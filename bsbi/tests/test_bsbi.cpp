#include "../bsbi.h"

#include <gtest/gtest.h>

class BlockProcessorTestFixture : public testing::Test
{
protected:
    void SetUp() override {
        docs.push_back(document::Document(
            0,
            "url",
            { "term1", "term2", "term3" },
            { "term2", "term3", "term4" }));
        docs.push_back(document::Document(
            1,
            "url",
            { "term3", "term4", "term5" },
            { "term4", "term5", "term6" }));

        expected = {
            bsbi::Record(0, 0),
            bsbi::Record{1, 0},
            bsbi::Record{2, 0},
            bsbi::Record{1, 0},
            bsbi::Record{2, 0},
            bsbi::Record{3, 0},
            bsbi::Record{2, 1},
            bsbi::Record{3, 1},
            bsbi::Record{4, 1},
            bsbi::Record{3, 1},
            bsbi::Record{4, 1},
            bsbi::Record{5, 1}
        };
    }

    void TearDown() override {
        docs.clear();
    }

    std::vector<document::Document> docs;
    std::vector<bsbi::Record> expected;
};

TEST_F(BlockProcessorTestFixture, TestInvertedIndexForBlockSingleThread)
{
    bsbi::BlockProcessor blockProcessor;
    std::vector<bsbi::Record> actual = blockProcessor.processBlockSingleThread(docs.begin(), docs.end());
    ASSERT_EQ(actual, expected);
}

TEST_F(BlockProcessorTestFixture, TestInvertedIndexForBlock)
{
    bsbi::BlockProcessor blockProcessor;
    std::vector<bsbi::Record> actual = blockProcessor.processBlock(docs.begin(), docs.end(), 2);
    ASSERT_EQ(actual, expected);
}
