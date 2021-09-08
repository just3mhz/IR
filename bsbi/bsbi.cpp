#include "bsbi.h"

#include "record_merger.h"

namespace bsbi {

namespace {

std::string makeFilename(std::size_t blockNum)
{
    return "block_" + std::to_string(blockNum) + ".txt";
}

template<class Iterator>
void cleanTempFiles(Iterator begin, Iterator end)
{
    for (auto it = begin; it != end; ++it) {
        std::remove(it->c_str());
    }
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
    std::vector<std::string> tempFiles;

    while (!reader.allDocsRead()) {
        for(int i = 0; i < blockSize_ && !reader.allDocsRead(); ++i) {
            block.push_back(reader.readNext());
        }

        auto records = blockProcessor_.processBlock(block.begin(), block.end());
        std::sort(records.begin(), records.end());

        ++blocksProcessed;

        tempFiles.push_back(makeFilename(blocksProcessed));
        recordDumper_->dump(tempFiles.back(), records);

        block.clear();
    }

    RecordMerger::merge(tempFiles);
    cleanTempFiles(tempFiles.begin(), tempFiles.end());

    auxiliary::SingletonDictionary::getInstance().dump("dict.json");
}

}