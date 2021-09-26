#include "../set_operations.h"
#include "../tokenization.h"

#include "gtest/gtest.h"

using namespace boolean_queries;

namespace {

template<class T>
std::shared_ptr<T> cast(const std::shared_ptr<Token>& token) {
    return std::dynamic_pointer_cast<T>(token);
}

bool equal(
    const std::shared_ptr<Token>& lhs,
    const std::shared_ptr<Token>& rhs)
{
    if (lhs->tokenType() != rhs->tokenType()) {
        return false;
    }

    switch (lhs->tokenType()) {
    case TokenType::TERM:
        return cast<Term>(lhs)->term() == cast<Term>(rhs)->term();
    case TokenType::OPERATOR:
        return cast<Operator>(lhs)->operatorType() == cast<Operator>(rhs)->operatorType();
    case TokenType::BRACKET:
        return cast<Bracket>(lhs)->isOpen() == cast<Bracket>(rhs)->isOpen();
    }

    return false;
}

} // namespace

class TestSetOperationsFixture: public testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::vector<uint64_t> lhs = {1, 3, 4, 7, 10, 11, 12};
    std::vector<uint64_t> rhs = {3, 5, 6, 7, 9, 11, 14, 15};
};

TEST_F(TestSetOperationsFixture, TestIntersect)
{
    const std::vector<uint64_t> expected = {3, 7, 11};
    ASSERT_EQ(sortedIntersect(lhs, rhs), expected);
}

TEST_F(TestSetOperationsFixture, TestJoin)
{
    const std::vector<uint64_t> expected = {1, 3, 4, 5, 6, 7, 9, 10, 11, 12, 14, 15};
    ASSERT_EQ(sortedJoin(lhs, rhs), expected);
}

TEST(TestParsing, TestTokenization)
{
    const std::string rawExpression = "abc && (cd || e)";
    const std::vector<std::shared_ptr<Token>> expected = {
        std::make_shared<Term>("abc"),
        std::make_shared<Operator>(Operator::Type::AND),
        std::make_shared<Bracket>(Bracket::Type::OPEN),
        std::make_shared<Term>("cd"),
        std::make_shared<Operator>(Operator::Type::OR),
        std::make_shared<Term>("e"),
        std::make_shared<Bracket>(Bracket::Type::CLOSE),
    };

    std::vector<std::shared_ptr<Token>> actual = tokenizeExpression(rawExpression);
    ASSERT_EQ(expected.size(), actual.size());
    for(int i = 0; i < expected.size(); ++i) {
        ASSERT_TRUE(equal(expected[i], actual[i]));
    }
}