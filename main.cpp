#include "boolean_queries/parser.h"
#include "boolean_queries/tokenization.h"

int main() {
    std::string expression = "abc && cd || e && (fg && hk)";
    std::cout << "Raw: " << expression << std::endl;

    auto tokens = boolean_queries::tokenizeExpression(expression);
    std::cout << "Tokenized: ";
    for(const auto& token: tokens) {
        std::cout << *token << ' ';
    }
    std::cout << std::endl;

    auto parsedExpression = boolean_queries::reversePolishNotation(tokens);
    std::cout << "Parsed: ";
    for(const auto& token: parsedExpression) {
        std::cout << *token << ' ';
    }
    return 0;
}
