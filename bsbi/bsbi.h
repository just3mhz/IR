#pragma once

#include "record.h"
#include "block_processor.h"
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
private:
    std::size_t blockSize_;
    std::shared_ptr<tokenization::Tokenizer> tokenizer_;
    std::unique_ptr<RecordDumper> recordDumper_;

    BlockProcessor blockProcessor_;
};

}
