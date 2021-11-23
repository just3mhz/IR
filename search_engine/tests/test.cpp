#include "../search_engine.h"

#include <iostream>
#include "gtest/gtest.h"

class MockIndexProvider final: public bsbi::InvIndexProvider {
public:
    std::vector<std::uint64_t> getDocIds(const std::string &term) const override {
        if (term == "abc")
            return {1, 2, 6, 8, 11, 14};
        if (term == "def")
            return {2, 3, 4, 6, 7, 8};
        if (term == "kde")
            return {2, 9, 11, 14, 15, 128};
        if (term == "a")
            return {1, 2 ,3};
        return {};
    }

    std::vector<uint64_t> getDocIds(const uint64_t termId) const override {
        return {};
    }

    const std::vector<uint64_t>& getDocIds() const override {
        const static std::vector<uint64_t> docIds{1, 2, 3, 4, 6, 7, 8, 9, 11, 14, 15, 128};
        return docIds;
    }
};

class SearchEngineFixture: public testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {

    }

    search_engine::SearchEngine engine_{std::make_shared<MockIndexProvider>()};
};

TEST_F(SearchEngineFixture, TestSingleWord) {
    std::vector<uint64_t> expected = {1, 2, 6, 8, 11, 14};
    ASSERT_EQ(engine_.search("abc"), expected);
}

TEST_F(SearchEngineFixture, TestUnknownWord) {
    ASSERT_EQ(engine_.search("unknown"), std::vector<uint64_t>());
}

TEST_F(SearchEngineFixture, TestOR) {
    std::vector<uint64_t> expected = {1, 2, 3, 4, 6, 7, 8};
    ASSERT_EQ(engine_.search("a || def"), expected);
    ASSERT_EQ(engine_.search("def || a"), expected);
}

TEST_F(SearchEngineFixture, TestAND) {
    std::vector<uint64_t> expected = {2, 3};
    ASSERT_EQ(engine_.search("a && def"), expected);
    ASSERT_EQ(engine_.search("def && a"), expected);
}

TEST_F(SearchEngineFixture, TestNOT)
{
    std::vector<uint64_t> expected = {4, 6, 7, 8, 9, 11, 14, 15, 128};
    ASSERT_EQ(engine_.search("!! a"), expected);
}

TEST_F(SearchEngineFixture, TestAND_NOT)
{
    std::vector<uint64_t> expected = {4, 6, 7, 8};
    ASSERT_EQ(engine_.search("!! a && def"), expected);
    ASSERT_EQ(engine_.search("def && !! a"), expected);
}

TEST_F(SearchEngineFixture, TestLong) {
    std::vector<uint64_t> expected = {2};
    ASSERT_EQ(engine_.search("a && abc && def && kde"), expected);
}

TEST_F(SearchEngineFixture, TestANDWithUnknownWord) {
    std::vector<uint64_t> expected = {};
    ASSERT_EQ(engine_.search("abc && abcd"), expected);
}

TEST_F(SearchEngineFixture, TestORWithUnknownWord) {
    std::vector<uint64_t> expected = {1, 2, 6, 8, 11, 14};
    ASSERT_EQ(engine_.search("abc || abcd"), expected);
}