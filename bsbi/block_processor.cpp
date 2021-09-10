#include "block_processor.h"

#include "../auxiliary/dictionary.h"

#include <future>
#include <cassert>

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
    return processBlockSingleThread(begin, end);
}

template std::vector<Record> BlockProcessor::processBlockSingleThread(std::vector<document::Document>::iterator begin, std::vector<document::Document>::iterator end);
template std::vector<Record> BlockProcessor::processBlock(std::vector<document::Document>::iterator begin, std::vector<document::Document>::iterator end, size_t threads);

}