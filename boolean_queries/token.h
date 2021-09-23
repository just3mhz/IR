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
        OR
    };

    virtual Type operatorType() const = 0;
    virtual int priority() const = 0;

    // Token
    TokenType tokenType() const override;

protected:
    constexpr static int LOW_PRIORITY = 0;
    constexpr static int HIGH_PRIORITY = 1;
};

class OperatorAND final: public Operator {
public:
    Type operatorType() const override;
    int priority() const override;
};

class OperatorOR final: public Operator {
public:
    Type operatorType() const override;
    int priority() const override;
};

std::ostream& operator<<(std::ostream& os, const Token& token);
std::ostream& operator<<(std::ostream& os, const Term& token);
std::ostream& operator<<(std::ostream& os, const Bracket& token);
std::ostream& operator<<(std::ostream& os, const Operator& token);
std::ostream& operator<<(std::ostream& os, const OperatorAND& token);
std::ostream& operator<<(std::ostream& os, const OperatorOR& token);

}
