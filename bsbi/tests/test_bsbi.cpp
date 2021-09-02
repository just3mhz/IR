#include "../bsbi.h"

#include <gtest/gtest.h>

class BsbiTestFixture: public testing::Test
{
protected:
    void SetUp() override {

    }

    void TearDown() override {
        auxiliary::SingletonDictionary::getInstance().clear();
    }
};

TEST_F(BsbiTestFixture, TestInvertedIndexForBlock)
{
    std::vector<tokenization::TokenizedDocument> docs;
    docs.push_back({
        .docId=0,
        .url="url",
        .tokenizedTitle={"term1", "term2", "term3"},
        .tokenizedText={"term2", "term3", "term4"}});
    docs.push_back({
        .docId=1,
        .url="url",
        .tokenizedTitle={"term3", "term4", "term5"},
        .tokenizedText={"term4", "term5", "term6"}});


    std::vector<bsbi::Record> actual = bsbi::invertedIndexForBlock(docs.begin(), docs.end());
    std::vector<bsbi::Record> expected = {
        {.termId=0, .docId=0},
        {.termId=1, .docId=0},
        {.termId=2, .docId=0},
        {.termId=1, .docId=0},
        {.termId=2, .docId=0},
        {.termId=3, .docId=0},
        {.termId=2, .docId=1},
        {.termId=3, .docId=1},
        {.termId=4, .docId=1},
        {.termId=3, .docId=1},
        {.termId=4, .docId=1},
        {.termId=5, .docId=1}};

    ASSERT_EQ(actual, expected);
}
