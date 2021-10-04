#pragma once

#include "record.h"
#include "block_processor.h"
#include "../document/document.h"
#include "../document/document_reader.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <future>
#include <filesystem>

namespace bsbi {

class BlockedSortBasedIndexer {
public:
    BlockedSortBasedIndexer(std::size_t blockSize);

    void makeIndex(
        const std::filesystem::path& inputFilePath,
        const std::filesystem::path& outputFilePath);
private:
    std::size_t blockSize_;
    std::shared_ptr<tokenization::Tokenizer> tokenizer_;

    BlockProcessor blockProcessor_;
};

}
