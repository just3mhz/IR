#pragma once

#include <iostream>

namespace boolean_queries {

enum TokenType {
    TERM,
    OPERATOR,
    BRACKET
};

class Token {
public:
    virtual TokenType tokenType() const = 0;
};

class Term final: public Token {
public:
    Term(uint64_t termId, std::string term);

    uint64_t termId() const;
    const std::string& term() const;

    // Token
    TokenType tokenType() const override;
private:
    uint64_t termId_;
    std::string term_;
};

class Bracket: public Token {
public:
    enum Type {
        OPEN,
        CLOSE
    };

    explicit Bracket(Type bracketType);

    TokenType tokenType() const override;

    bool isOpen() const;
    bool isClose() const;
private:
    Type type_;
};

class Operator: public Token {
public:
    TokenType tokenType() const override;

    int priority() const;
};

}
