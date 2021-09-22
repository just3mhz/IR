#pragma once

#include "token.h"

#include <iostream>
#include <memory>
#include <stack>
#include <vector>

namespace boolean_queries {

std::vector<std::shared_ptr<Token>> reversePolishNotation(const std::vector<std::shared_ptr<Token>>& tokens)
{
    std::vector<std::shared_ptr<Token>> outputTokens;
    std::stack<std::shared_ptr<Token>> operators;

    for(const std::shared_ptr<Token>& token: tokens) {
        if (token->tokenType() == TokenType::TERM) {
            outputTokens.push_back(token);
        } else if (token->tokenType() == TokenType::OPERATOR) {
            const auto op1 = std::dynamic_pointer_cast<Operator>(token);
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
        } else if (token->tokenType() == TokenType::BRACKET) {
            const auto bracket = std::dynamic_pointer_cast<Bracket>(token);
            if (bracket->isOpen()) {
                operators.push(bracket);
            } else {
                while(!operators.empty() && operators.top()->tokenType() != TokenType::BRACKET) {
                    outputTokens.push_back(operators.top());
                    operators.pop();
                }

                if (operators.empty())
                    throw std::runtime_error("Unable to parse expression");
                operators.pop();
            }
        }
    }

    while (!operators.empty()) {
        if (operators.top()->tokenType() == TokenType::BRACKET)
            throw std::runtime_error("Unable to parse expression");
        outputTokens.push_back(operators.top());
        operators.pop();
    }

    return outputTokens;
}

}
