#include "../dictionary.h"

#include <gtest/gtest.h>

TEST(SingletonDictionary, BaseTest)
{
    ASSERT_EQ(auxiliary::SingletonDictionary::getInstance().getTermId("term1"), 0);
    ASSERT_EQ(auxiliary::SingletonDictionary::getInstance().getTermId("term2"), 1);
    ASSERT_EQ(auxiliary::SingletonDictionary::getInstance().getTermId("term3"), 2);

    ASSERT_EQ(auxiliary::SingletonDictionary::getInstance().getTermId("term1"), 0);

    ASSERT_TRUE(auxiliary::SingletonDictionary::getInstance().hasTerm("term1"));
    ASSERT_FALSE(auxiliary::SingletonDictionary::getInstance().hasTerm("term5"));
}