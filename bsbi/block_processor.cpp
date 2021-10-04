#include "block_processor.h"

#include "../common/handler.h"

#include <cassert>

namespace bsbi {

template <class Iterator>
std::vector<Record> BlockProcessor::processBlockSingleThread(Iterator begin, Iterator end)
{
    common::PerformanceHandler performanceHandler("process_block_single_thread");

    std::vector<Record> records;

    auto processText = [this, &records](const std::vector<std::string>& text, uint64_t docId) {
        for (const std::string& term : text) {
            if (!dict_.contains(term)) {
                dict_.insert(term, dict_.size());
            }
            records.emplace_back(dict_.at(term), docId);
        }
    };

    for (Iterator it = begin; it != end; ++it) {
        const document::Document& doc = *it;
        processText(doc.title(), doc.id());
        processText(doc.text(), doc.id());
    }
    return records;
}

template <class Iterator>
std::vector<Record> BlockProcessor::processBlock(Iterator begin, Iterator end, size_t threads)
{
    assert(threads > 0);
    return processBlockSingleThread(begin, end);
}

const common::Dictionary& BlockProcessor::dictionary() const
{
    return dict_;
}

template std::vector<Record> BlockProcessor::processBlockSingleThread(std::vector<document::Document>::iterator begin, std::vector<document::Document>::iterator end);
template std::vector<Record> BlockProcessor::processBlock(std::vector<document::Document>::iterator begin, std::vector<document::Document>::iterator end, size_t threads);

}