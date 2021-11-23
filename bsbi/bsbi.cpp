#include "bsbi.h"

#include "record_merger.h"
#include "../common/serialization/serialize.h"
#include "../common/handler.h"
#include "../document/document_index.h"

#include <boost/log/trivial.hpp>

namespace bsbi {

namespace {

std::filesystem::path makeFilename(const std::filesystem::path& dir, std::size_t blockNum)
{
    return dir / ("block_" + std::to_string(blockNum) + ".records   ");
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
    common::PerformanceHandler performanceHandler("dump_records");
    std::ofstream ofs(outputPath, std::ios::binary);
    common::serialization::write(ofs, records.size());
    for(const auto& record: records) {
        common::serialization::write(ofs, record);
    }
}

std::vector<document::Document> readNextBlock(const std::size_t blockSize, document::DocumentReader& reader)
{
    common::PerformanceHandler performanceHandler("read_block");
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
    const std::filesystem::path& outputDirectory)
{
    common::PerformanceHandler performanceHandler("make_index");

    if (!std::filesystem::exists(outputDirectory)) {
        std::filesystem::create_directories(outputDirectory);
    }
    assert(std::filesystem::is_directory(outputDirectory));

    document::DocumentReader reader(inputFilePath, blockSize_, tokenizer_.get());

    std::size_t blocksProcessed = 0;
    std::vector<std::filesystem::path> tempFiles;
    auto documentIndex = document::createDocumentIndex();

    while (!reader.allDocsRead()) {
        auto block = readNextBlock(blockSize_, reader);

        for(const auto& doc: block) {
            documentIndex->appendDocument(doc);
        }

        auto records = blockProcessor_.processBlock(block.begin(), block.end());

        std::sort(records.begin(), records.end());

        ++blocksProcessed;

        tempFiles.push_back(makeFilename(outputDirectory, blocksProcessed));
        dumpRecords(records, tempFiles.back());
    }

    RecordMerger::merge(tempFiles, outputDirectory);
    cleanTempFiles(tempFiles.begin(), tempFiles.end());

    std::ofstream dictOfs(outputDirectory / "dict.bin");
    common::serialization::write(dictOfs, blockProcessor_.dictionary());

    std::ofstream documentIndexStream(outputDirectory / "document_index.bin");
    common::serialization::write(documentIndexStream, *documentIndex);
}

}