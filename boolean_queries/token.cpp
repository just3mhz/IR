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

int Operator::priority() const
{
    return 0;
}

}