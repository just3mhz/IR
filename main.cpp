#include "boolean_queries/parser.h"
#include "boolean_queries/expression_tree.h"
#include "boolean_queries/tokenization.h"

class MockInvertedIndexProvider: public InvertedIndexProvider {
    std::vector<std::uint64_t> getDocIds(const std::string &term) const override {
        if (term == "abc") {
            return {1, 3, 6, 8, 9};
        } else if (term == "cd") {
            return {1, 5, 8};
        } else {
            return {1, 3, 6};
        }
    }
};

int main() {
    std::string expression = "abc && cd";
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
    std::cout << std::endl;

    boolean_queries::ExpressionTree tree(parsedExpression);

    std::cout << "Search result: ";
    for(auto doc: tree.evaluate(MockInvertedIndexProvider())) {
        std::cout << doc << ' ';
    }
    std::cout << std::endl;

    return 0;
}
