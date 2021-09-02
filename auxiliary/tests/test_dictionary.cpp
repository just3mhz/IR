#include "../dictionary.h"

#include <fstream>

#include <gtest/gtest.h>

class DictFixture: public testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
        dict_.clear();
    }

    auxiliary::SingletonDictionary& dict_{auxiliary::SingletonDictionary::getInstance()};
};

TEST_F(DictFixture, BaseTest)
{
    ASSERT_EQ(dict_.getTermId("term1"), 0);
    ASSERT_EQ(dict_.getTermId("term2"), 1);
    ASSERT_EQ(dict_.getTermId("term3"), 2);

    ASSERT_EQ(dict_.getTermId("term1"), 0);

    ASSERT_TRUE(dict_.hasTerm("term1"));
    ASSERT_FALSE(dict_.hasTerm("term5"));
}

TEST_F(DictFixture, TestClear)
{
   ASSERT_FALSE(dict_.hasTerm("term1"));

   dict_.getTermId("term1");

   ASSERT_TRUE(dict_.hasTerm("term1"));

   dict_.clear();

   ASSERT_FALSE(dict_.hasTerm("term1"));
}

TEST_F(DictFixture, TestDump)
{
    ASSERT_FALSE(dict_.hasTerm("term1"));
    ASSERT_FALSE(dict_.hasTerm("term2"));
    ASSERT_FALSE(dict_.hasTerm("term3"));

    dict_.getTermId("term1");
    dict_.getTermId("term2");
    dict_.getTermId("term3");

    ASSERT_TRUE(dict_.hasTerm("term1"));
    ASSERT_TRUE(dict_.hasTerm("term2"));
    ASSERT_TRUE(dict_.hasTerm("term3"));

    dict_.dump("dump.json");

    std::vector<std::string> expectedDump = {
        "{",
        "    \"term1\":0,",
        "    \"term2\":1,",
        "    \"term3\":2",
        "}"
    };

    std::ifstream ifs("dump.json");
    ASSERT_TRUE(ifs.is_open());

    auto it = expectedDump.begin();
    std::string currentLine;
    while(std::getline(ifs, currentLine, '\n')) {
        ASSERT_EQ(currentLine, *it);
        ++it;
    }

    std::remove("dump.json");
}