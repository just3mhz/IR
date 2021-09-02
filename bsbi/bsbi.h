#pragma once

#include "../tokenization/tokenization.h"
#include "../auxiliary/dictionary.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <future>

namespace bsbi {

struct Record
{
    uint64_t termId;
    uint64_t docId;

    bool operator==(const Record& other) const {
        return termId == other.termId && docId == other.docId;
    }
};

template<class Iterator>
std::vector<Record> invertedIndexForBlockSingleThread(Iterator begin, Iterator end)
{
    std::vector<Record> records;
    auto& dict = auxiliary::SingletonDictionary::getInstance();
    for(Iterator it = begin; it != end; ++it) {
        const tokenization::TokenizedDocument& doc = *it;
        for(const std::string& term: doc.tokenizedTitle) {
            records.push_back({ dict.getTermId(term), doc.docId });
        }
        for(const std::string& term: doc.tokenizedText) {
            records.push_back({ dict.getTermId(term), doc.docId });
        }
    }
    return records;
}

template<class Iterator>
std::vector<Record> invertedIndexForBlock(Iterator begin, Iterator end, size_t threads=1)
{
    assert(threads > 0);

    size_t blockSize = static_cast<size_t>(end - begin);
    size_t step = blockSize / threads;

    std::vector<std::future<std::vector<Record>>> futures;
    for(size_t offset = 0; offset < blockSize; offset += step) {
        futures.push_back(
            std::async(invertedIndexForBlockSingleThread<Iterator>,
                       begin + offset,
                       begin + std::min(offset + step, blockSize)));
    }

    std::vector<Record> result;
    for(auto& future: futures) {
        std::vector<Record> subResult = future.get();
        result.insert(
            result.end(),
            std::make_move_iterator(subResult.begin()),
            std::make_move_iterator(subResult.end()));
    }

    return result;
}

}
