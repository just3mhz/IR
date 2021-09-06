#include "block_processor.h"

#include "../auxiliary/dictionary.h"

#include <future>

namespace bsbi {

template <class Iterator>
std::vector<Record> BlockProcessor::processBlockSingleThread(Iterator begin, Iterator end)
{
    std::vector<Record> records;
    auto& dict = auxiliary::SingletonDictionary::getInstance();
    for (Iterator it = begin; it != end; ++it) {
        const document::Document& doc = *it;
        for (const std::string& term : doc.title())
            records.push_back({ dict.getTermId(term), doc.id() });
        for (const std::string& term : doc.text())
            records.push_back({ dict.getTermId(term), doc.id() });
    }
    return records;
}

template <class Iterator>
std::vector<Record> BlockProcessor::processBlock(Iterator begin, Iterator end, size_t threads)
{
    assert(threads > 0);

    std::size_t blockSize = static_cast<std::size_t>(end - begin);
    std::size_t step = blockSize / threads;

    std::vector<std::future<std::vector<Record>>> futures;
    for (std::size_t offset = 0; offset < blockSize; offset += step) {
        futures.push_back(
            std::async(&BlockProcessor::processBlockSingleThread<Iterator>, this,
                begin + offset,
                begin + std::min(offset + step, blockSize)));
    }

    std::vector<Record> result;
    for (auto& future : futures) {
        std::vector<Record> subResult = future.get();
        result.insert(
            result.end(),
            std::make_move_iterator(subResult.begin()),
            std::make_move_iterator(subResult.end()));
    }

    return result;
}

template std::vector<Record> BlockProcessor::processBlockSingleThread(std::vector<document::Document>::iterator begin, std::vector<document::Document>::iterator end);
template std::vector<Record> BlockProcessor::processBlock(std::vector<document::Document>::iterator begin, std::vector<document::Document>::iterator end, size_t threads);

}