#include "record_merger.h"

#include "../common/handler.h"
#include "../common/serialization/serialize.h"
#include "postings/posting_list_builder.h"

#include <cassert>
#include <chrono>
#include <fstream>
#include <optional>
#include <set>

#include <boost/log/trivial.hpp>

namespace bsbi {

namespace {

class Reader {
public:
    explicit Reader(const std::vector<std::filesystem::path>& inputPaths)
        : streams_(inputPaths.size())
        , recordsCount_(inputPaths.size())
    {
        for (std::size_t i = 0; i < inputPaths.size(); ++i) {
            streams_[i] = std::ifstream(inputPaths[i]);
            common::serialization::read(streams_[i], recordsCount_[i]);
            readFromStream(i);
        }
    }

    bool empty()
    {
        return priorityQueue_.empty();
    }

    const Record& current()
    {
        return priorityQueue_.begin()->first;
    }

    void readNext()
    {
        const std::size_t streamId = priorityQueue_.begin()->second;
        priorityQueue_.erase(priorityQueue_.begin());
        readFromStream(streamId);
    }

private:
    void readFromStream(std::size_t streamId)
    {
        if (recordsCount_[streamId] == 0) {
            return;
        }

        Record record;
        common::serialization::read(streams_[streamId], record);
        --recordsCount_[streamId];
        priorityQueue_.emplace(record, streamId);
    }

    std::vector<std::ifstream> streams_;
    std::vector<std::size_t> recordsCount_;
    std::set<std::pair<Record, std::size_t>> priorityQueue_;
};

} // namespace

void RecordMerger::merge(
    const std::vector<std::filesystem::path>& inputPaths,
    const std::filesystem::path& outputDir)
{
    common::PerformanceHandler performanceHandler("merge_processed_blocks");
    Reader recordReader(inputPaths);
    std::ofstream postingsOfs(outputDir / "postings.bin", std::ios::binary);
    std::ofstream offsetsOfs(outputDir / "offsets.bin", std::ios::binary);
    while (!recordReader.empty()) {
        const uint64_t termId = recordReader.current().termId;

        std::vector<uint64_t> docIds;
        while (!recordReader.empty() && termId == recordReader.current().termId) {
            docIds.push_back(recordReader.current().docId);
            recordReader.readNext();
        }
        const std::size_t pos = static_cast<std::size_t>(postingsOfs.tellp());
        const auto pList = postings::PostingListBuilder::makePostingList(termId, docIds);
        common::serialization::write(postingsOfs, pList);

        common::serialization::write(offsetsOfs, termId);
        common::serialization::write(offsetsOfs, pos);
    }
}

}