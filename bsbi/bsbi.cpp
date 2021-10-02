#include "bsbi.h"

#include "record_merger.h"
#include "../common/serialization/serialize.h"
#include "../common/handler.h"

#include <source_location>

namespace bsbi {

namespace {

std::filesystem::path makeFilename(std::size_t blockNum)
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

void dumpRecords(const std::vector<Record>& records, const std::filesystem::path& outputPath)
{
    std::ofstream ofs(outputPath, std::ios::binary);
    common::serialization::write(ofs, records.size());
    for(const auto& record: records) {
        common::serialization::write(ofs, record);
    }
}

std::vector<document::Document> readNextBlock(const std::size_t blockSize, document::DocumentReader& reader)
{
    std::vector<document::Document> block;
    block.reserve(blockSize);
    for(int i = 0; i < blockSize && !reader.allDocsRead(); ++i) {
        block.push_back(reader.readNext());
    }
    return block;
}

}

BlockedSortBasedIndexer::BlockedSortBasedIndexer(std::size_t blockSize)
    : blockSize_(blockSize)
    , tokenizer_(std::make_shared<tokenization::SimpleTokenizer>())
{
}

void BlockedSortBasedIndexer::makeIndex(
    const std::filesystem::path& inputFilePath,
    const std::filesystem::path& outputFilePath)
{
    common::PerformanceHandler performanceHandler("make_index");

    document::DocumentReader reader(inputFilePath, blockSize_, tokenizer_.get());

    std::size_t blocksProcessed = 0;
    std::vector<std::filesystem::path> tempFiles;

    while (!reader.allDocsRead()) {
        auto block = readNextBlock(blockSize_, reader);
        auto records = blockProcessor_.processBlock(block.begin(), block.end());

        std::sort(records.begin(), records.end());

        ++blocksProcessed;

        tempFiles.push_back(makeFilename(blocksProcessed));
        dumpRecords(records, tempFiles.back());

        block.clear();
    }

    RecordMerger::merge(tempFiles, outputFilePath);
    cleanTempFiles(tempFiles.begin(), tempFiles.end());

    auxiliary::SingletonDictionary::getInstance().dump("dict.json");
}

}