#include "../bsbi.h"

#include <gtest/gtest.h>

class BsbiTestFixture: public testing::Test
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
            { .termId = 0, .docId = 0 },
            { .termId = 1, .docId = 0 },
            { .termId = 2, .docId = 0 },
            { .termId = 1, .docId = 0 },
            { .termId = 2, .docId = 0 },
            { .termId = 3, .docId = 0 },
            { .termId = 2, .docId = 1 },
            { .termId = 3, .docId = 1 },
            { .termId = 4, .docId = 1 },
            { .termId = 3, .docId = 1 },
            { .termId = 4, .docId = 1 },
            { .termId = 5, .docId = 1 }
        };
    }

    void TearDown() override {
        docs.clear();
        expected.clear();
        auxiliary::SingletonDictionary::getInstance().clear();
    }

    std::vector<document::Document> docs;
    std::vector<bsbi::Record> expected;
};

TEST_F(BsbiTestFixture, TestInvertedIndexForBlockSingleThread)
{
    std::vector<bsbi::Record> actual = bsbi::invertedIndexForBlockSingleThread(docs.begin(), docs.end());
    ASSERT_EQ(actual, expected);
}

TEST_F(BsbiTestFixture, TestInvertedIndexForBlock)
{
    std::vector<bsbi::Record> actual = bsbi::invertedIndexForBlock(docs.begin(), docs.end(), 2);
    ASSERT_EQ(actual, expected);
}
