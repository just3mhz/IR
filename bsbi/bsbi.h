#pragma once

#include "record.h"
#include "../document/document.h"
#include "../document/document_reader.h"
#include "../auxiliary/dictionary.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <future>

namespace bsbi {

class BlockedSortBasedIndexer {
public:
    BlockedSortBasedIndexer(std::size_t blockSize);

    void makeIndex(const std::string& inputFilePath, const std::string& outputFilePath);

    // TODO: Move to BlockProcessor
    template<class Iterator>
    std::vector<Record> processBlock(Iterator begin, Iterator end, size_t threads=1);

    // TODO: Move to BlockProcessor
    template<class Iterator>
    std::vector<Record> processBlockSingleThread(Iterator begin, Iterator end);
private:
    std::size_t blockSize_;
    std::shared_ptr<tokenization::Tokenizer> tokenizer_;
    std::unique_ptr<RecordDumper> recordDumper_;
};

template<class Iterator>
std::vector<Record> BlockedSortBasedIndexer::processBlockSingleThread(Iterator begin, Iterator end)
{
    std::vector<Record> records;
    auto& dict = auxiliary::SingletonDictionary::getInstance();
    for(Iterator it = begin; it != end; ++it) {
        const document::Document& doc = *it;
        for(const std::string& term: doc.title())
            records.push_back({dict.getTermId(term), doc.id()});
        for(const std::string& term: doc.text())
            records.push_back({dict.getTermId(term), doc.id()});
    }
    return records;
}

template<class Iterator>
std::vector<Record> BlockedSortBasedIndexer::processBlock(Iterator begin, Iterator end, size_t threads)
{
    assert(threads > 0);

    size_t blockSize = static_cast<size_t>(end - begin);
    size_t step = blockSize / threads;

    std::vector<std::future<std::vector<Record>>> futures;
    for(size_t offset = 0; offset < blockSize; offset += step) {
        futures.push_back(
            std::async(&BlockedSortBasedIndexer::processBlockSingleThread<Iterator>, this,
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
