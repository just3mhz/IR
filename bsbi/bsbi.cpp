#include "bsbi.h"

namespace bsbi {

namespace {

std::string makeFilename(std::size_t blockNum)
{
    return "block_" + std::to_string(blockNum) + ".txt";
}

}

BlockedSortBasedIndexer::BlockedSortBasedIndexer(std::size_t blockSize)
    : blockSize_(blockSize)
    , tokenizer_(std::make_shared<tokenization::SimpleTokenizer>())
    , recordDumper_(std::make_unique<RecordDumperTxt>())
{
}

void BlockedSortBasedIndexer::makeIndex(const std::string& inputFilePath, const std::string& outputFilePath)
{
    document::DocumentReader reader(inputFilePath, blockSize_, tokenizer_.get());
    std::vector<document::Document> block;
    block.reserve(blockSize_);

    std::size_t blocksProcessed = 0;

    while (!reader.allDocsRead()) {
        for(int i = 0; i < blockSize_ && !reader.allDocsRead(); ++i) {
            block.push_back(reader.readNext());
        }

        auto records = processBlockSingleThread(block.begin(), block.end());
        std::sort(records.begin(), records.end());

        ++blocksProcessed;

        recordDumper_->dump(makeFilename(blocksProcessed), records);
        block.clear();
    }

    auxiliary::SingletonDictionary::getInstance().dump("dict.json");
}

}