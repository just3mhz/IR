#include "record_merger.h"

#include "postings/posting_list_builder.h"

#include <fstream>
#include <set>
#include <optional>

namespace bsbi {


void RecordMerger::merge(const std::vector<std::string>& paths)
{
    std::vector<std::ifstream> streams;
    streams.reserve(paths.size());
    for (const auto& path: paths) {
        streams.emplace_back(path);
    }

    std::set<std::pair<Record, std::size_t>> pq;

    for(int i = 0; i < streams.size(); ++i) {
        Record record;
        if (streams[i] >> record.termId >> record.docId) {
            pq.emplace(record, i);
        }
    }

    std::ofstream ofs("output.txt");
    std::optional<postings::PostingListBuilder> builder;
    while ( !pq.empty() ) {
        const auto item = *pq.begin();
        pq.erase(*pq.begin());

        Record record = item.first;
        std::size_t streamId = item.second;

        Record nextRecord;
        if (streams[streamId] >> nextRecord.termId >> nextRecord.docId) {
            pq.emplace(nextRecord, streamId);
        }

        if (builder && builder->termId() == record.termId) {
            builder->processRecord(record);
            continue;
        }

        if (builder)
            ofs << builder->createPostingList() << '\n';

        builder = postings::PostingListBuilder(record.termId);
        builder->processRecord(record);
    }

    ofs.close();
}

}