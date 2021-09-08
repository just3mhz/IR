#include "record_merger.h"

#include "posting.h"

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
    std::optional<Posting> currentPosting;
    while ( !pq.empty() ) {
        const auto item = *pq.begin();
        pq.erase(*pq.begin());

        Record record = item.first;
        std::size_t streamId = item.second;

        Record nextRecord;
        if (streams[streamId] >> nextRecord.termId >> nextRecord.docId) {
            pq.emplace(nextRecord, streamId);
        }

        if (currentPosting && currentPosting->termId() == record.termId) {
            currentPosting->pushDocId(record.docId);
            continue;
        }

        if (currentPosting)
            currentPosting->printPosting(ofs);

        currentPosting = Posting(record.termId);
        currentPosting->pushDocId(record.docId);
    }

    ofs.close();
}

}