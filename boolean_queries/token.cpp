#include "token.h"

namespace boolean_queries {

Term::Term(std::string term)
    : term_(std::move(term))
{ }

const std::string& Term::term() const
{
    return term_;
}

TokenType Term::tokenType() const
{
    return TokenType::TERM;
}

Bracket::Bracket(Type bracketType)
    : type_(bracketType)
{ }

bool Bracket::isOpen() const
{
    return type_ == Type::OPEN;
}

bool Bracket::isClose() const
{
    return type_ == Type::CLOSE;
}

TokenType Bracket::tokenType() const
{
    return TokenType::BRACKET;
}

Operator::Operator(Operator::Type operatorType)
    : type_(operatorType)
{
}

TokenType Operator::tokenType() const
{
    return TokenType::OPERATOR;
}

Operator::Type Operator::operatorType() const
{
    return type_;
}

int Operator::priority() const
{
    switch (type_) {
    case AND:
        return HIGH_PRIORITY;
    case OR:
        return LOW_PRIORITY;
    case NOT:
        return UNARY_PRIORITY;
    }
    throw std::runtime_error("Unknown operator type");
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
    switch (token.tokenType()) {
    case TokenType::TERM:
        return os << dynamic_cast<const Term&>(token);
    case OPERATOR:
        return os << dynamic_cast<const Operator&>(token);
    case BRACKET:
        return os << dynamic_cast<const Bracket&>(token);
    }
    throw std::runtime_error("Unknown TokenType");
}

std::ostream& operator<<(std::ostream& os, const Term& token)
{
    return os << token.term();
}

std::ostream& operator<<(std::ostream& os, const Bracket& token)
{
    if (token.isOpen()) {
        return os << '(';
    }
    return os << ')';
}

std::ostream& operator<<(std::ostream& os, const Operator& token)
{
    switch (token.operatorType()) {
    case Operator::Type::AND:
        return os << "&&";
    case Operator::Type::OR:
        return os << "||";
    case Operator::Type::NOT:
        return os << "!!";
    }
    throw std::runtime_error("Unknown Operator::Type");
}

}