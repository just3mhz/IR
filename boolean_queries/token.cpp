#include "token.h"

namespace boolean_queries {

Term::Term(uint64_t termId, std::string term)
    : termId_(termId)
    , term_(std::move(term))
{ }

uint64_t Term::termId() const
{
    return termId_;
}

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

TokenType Operator::tokenType() const
{
    return TokenType::OPERATOR;
}

Operator::Type OperatorAND::operatorType() const
{
    return Operator::Type::AND;
}

int OperatorAND::priority() const
{
    return HIGH_PRIORITY;
}

Operator::Type OperatorOR::operatorType() const
{
    return Operator::Type::OR;
}

int OperatorOR::priority() const
{
    return LOW_PRIORITY;
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
        return os << dynamic_cast<const OperatorAND&>(token);
    case Operator::Type::OR:
        return os << dynamic_cast<const OperatorOR&>(token);
    }
    throw std::runtime_error("Unknown Operator::Type");
}

std::ostream& operator<<(std::ostream& os, const OperatorAND& token)
{
    return os << "&&";
}

std::ostream& operator<<(std::ostream& os, const OperatorOR& token)
{
    return os << "||";
}

}