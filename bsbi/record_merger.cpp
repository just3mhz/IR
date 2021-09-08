#include "record_merger.h"

#include <iostream>
#include <fstream>
#include <set>

namespace bsbi {

namespace {

struct Posting {
    uint64_t termId;
    std::vector<uint64_t> docIds;
    std::vector<uint64_t> counts;
};

}

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

    std::ofstream ifs("output.txt");
    Posting currentPosting{};
    while ( !pq.empty() ) {
        const auto item = *pq.begin();
        pq.erase(*pq.begin());

        Record record = item.first;
        std::size_t streamId = item.second;

        Record nextRecord;
        if (streams[streamId] >> nextRecord.termId >> nextRecord.docId) {
            pq.emplace(nextRecord, streamId);
        }

        if (currentPosting.termId == record.termId) {
            if (!currentPosting.docIds.empty() && currentPosting.docIds.back() == record.docId) {
                currentPosting.counts.back() += 1;
            } else {
                currentPosting.docIds.push_back(record.docId);
                currentPosting.counts.push_back(1);
            }
            continue;
        }

        ifs << "{ " << currentPosting.termId << " : [";
        std::sort(currentPosting.docIds.begin(), currentPosting.docIds.end());
        for(int i = 0; i < currentPosting.docIds.size(); ++i) {
            if (i != 0)
                ifs << ", ";
            ifs << "(" << currentPosting.docIds[i] << ", " << currentPosting.counts[i] << ")";
        }
        ifs << "] }\n";

        currentPosting.termId = record.termId;
        currentPosting.docIds.clear();
        currentPosting.counts.clear();

        currentPosting.docIds.push_back(record.docId);
        currentPosting.counts.push_back(1);
    }

    ifs.close();
}

}