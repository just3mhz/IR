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
    explicit Term(std::string term);
    const std::string& term() const;

    // Token
    TokenType tokenType() const override;
private:
    std::string term_;
};

class Bracket: public Token {
public:
    enum Type {
        OPEN,
        CLOSE
    };

    explicit Bracket(Type bracketType);

    bool isOpen() const;
    bool isClose() const;

    // Token
    TokenType tokenType() const override;
private:
    Type type_;
};

class Operator: public Token {
public:
    enum Type {
        AND,
        OR,
        NOT
    };

    explicit Operator(Type operatorType);

    Type operatorType() const;
    int priority() const;

    // Token
    TokenType tokenType() const override;
private:
    constexpr static int LOW_PRIORITY = 0;
    constexpr static int HIGH_PRIORITY = 1;
    constexpr static int UNARY_PRIORITY = 2;
    Type type_;
};

std::ostream& operator<<(std::ostream& os, const Token& token);
std::ostream& operator<<(std::ostream& os, const Term& token);
std::ostream& operator<<(std::ostream& os, const Bracket& token);
std::ostream& operator<<(std::ostream& os, const Operator& token);

}
