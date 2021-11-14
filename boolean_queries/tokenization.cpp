#include "tokenization.h"

namespace boolean_queries {

namespace {

bool isAND(std::size_t i, const std::string& rawExpression)
{
    return i < rawExpression.size() - 1
           && rawExpression[i] == '&'
           && rawExpression[i + 1] == '&';
}

bool isOR(std::size_t i, const std::string& rawExpression) {
    return i < rawExpression.size() - 1
           && rawExpression[i] == '|'
           && rawExpression[i + 1] == '|';
}

std::string extractTerm(std::size_t i, const std::string& rawExpression) {
    std::size_t j = i;
    while (j < rawExpression.size() && std::isalpha(rawExpression[j])) {
        ++j;
    }
    return rawExpression.substr(i, j - i);
}

} // namespace

std::vector<std::shared_ptr<Token>> tokenizeExpression(
    const std::string& rawExpression,
    const tokenization::WordTokenizer& wordTokenizer)
{
    std::vector<std::shared_ptr<Token>> tokens;
    std::size_t i = 0;
    while(i < rawExpression.size()) {
        if (rawExpression[i] == ' ') {
            i++;
        } else if (std::isalpha(rawExpression[i])) {
            auto term = extractTerm(i, rawExpression);
            i += term.size();
            tokens.push_back(std::make_shared<Term>(wordTokenizer.tokenize(term)));
        } else if (isAND(i, rawExpression)) {
            i += 2;
            tokens.push_back(std::make_shared<Operator>(Operator::Type::AND));
        } else if (isOR(i, rawExpression)) {
            i += 2;
            tokens.push_back(std::make_shared<Operator>(Operator::Type::OR));
        } else if (rawExpression[i] == '(') {
            i++;
            tokens.push_back(std::make_shared<Bracket>(Bracket::Type::OPEN));
        } else if (rawExpression[i] == ')') {
            i++;
            tokens.push_back(std::make_shared<Bracket>(Bracket::Type::CLOSE));
        } else {
            throw std::runtime_error("Unexpected character in expression");
        }
    }

    return tokens;
}

} // namespace boolean_queries