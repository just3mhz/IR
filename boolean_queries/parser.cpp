#include "parser.h"

namespace boolean_queries {

namespace {

void processOperator(
    const std::shared_ptr<Token>& token,
    std::vector<std::shared_ptr<Token>>& outputTokens,
    std::stack<std::shared_ptr<Token>>& operators)
{
    const auto& op1 = std::dynamic_pointer_cast<Operator>(token);
    while (!operators.empty()) {
        if (operators.top()->tokenType() == TokenType::BRACKET) {
            break;
        }
        const auto op2 = std::dynamic_pointer_cast<Operator>(operators.top());
        if (op2->priority() < op1->priority()) {
            break;
        }
        outputTokens.push_back(op2);
        operators.pop();
    }
    operators.push(op1);
}

void processBracket(
    const std::shared_ptr<Token>& token,
    std::vector<std::shared_ptr<Token>>& outputTokens,
    std::stack<std::shared_ptr<Token>>& operators)
{
    const auto bracket = std::dynamic_pointer_cast<Bracket>(token);

    if (bracket->isOpen()) {
        operators.push(bracket);
        return;
    }

    while (!operators.empty() && operators.top()->tokenType() != TokenType::BRACKET) {
        outputTokens.push_back(operators.top());
        operators.pop();
    }

    if (operators.empty())
        throw std::runtime_error("Unable to parse expression");
    operators.pop();
}

} // namespace

std::vector<std::shared_ptr<Token>> reversePolishNotation(const std::vector<std::shared_ptr<Token>>& tokens)
{
    std::vector<std::shared_ptr<Token>> outputTokens;
    std::stack<std::shared_ptr<Token>> operators;

    for (const auto& token : tokens) {
        switch (token->tokenType()) {
        case TERM:
            outputTokens.push_back(token);
            continue;
        case OPERATOR:
            processOperator(token, outputTokens, operators);
            continue;
        case BRACKET:
            processBracket(token, outputTokens, operators);
            continue;
        }
        throw std::runtime_error("Unknown TokenType");
    }

    while (!operators.empty()) {
        if (operators.top()->tokenType() == TokenType::BRACKET)
            throw std::runtime_error("Unable to parse expression");
        outputTokens.push_back(operators.top());
        operators.pop();
    }

    return outputTokens;
}

} // namespace boolean_queries
