#include "../dictionary.h"

#include <memory>

#include <gtest/gtest.h>


TEST(Dictionary, AddTerm)
{
    auto dict = std::make_shared<auxiliary::HashDictionary>();

    auto addTerm = [dict](const std::string& term, uint64_t termId) {
        ASSERT_FALSE(dict->hasTerm(term));
        dict->addTerm(term);
        ASSERT_TRUE(dict->hasTerm(term));
        ASSERT_EQ(dict->getTermId(term), termId);
    };

    addTerm("term1", 0);
    addTerm("term2", 1);
    addTerm("term3", 2);
}

TEST(Dictionary, GetNonExistantTerm)
{
    auto dict = std::make_shared<auxiliary::HashDictionary>();
    ASSERT_THROW(dict->getTermId("term1"), std::runtime_error);
}

TEST(Dictionary, AddExistingTerm)
{
    auto dict = std::make_shared<auxiliary::HashDictionary>();
    dict->addTerm("term1");

    ASSERT_THROW(dict->addTerm("term1"), std::runtime_error);
}