#pragma once

#include "token.h"

#include <vector>
#include <memory>

class InvertedIndexProvider {
public:
    virtual std::vector<std::uint64_t> getDocIds(const std::string& term) const = 0;
};

namespace boolean_queries {

class Node {
public:
    virtual std::vector<uint64_t> evaluate(const InvertedIndexProvider& invertedIndexProvider) const = 0;
    virtual const std::shared_ptr<Node>& left() const = 0;
    virtual const std::shared_ptr<Node>& right() const = 0;
    virtual void setLeft(std::shared_ptr<Node> left) = 0;
    virtual void setRight(std::shared_ptr<Node> right) = 0;
};

class ExpressionTree {
public:
    ExpressionTree() = default;
    explicit ExpressionTree(const std::vector<std::shared_ptr<Token>>& tokens);

    std::vector<uint64_t> evaluate(const InvertedIndexProvider& invertedIndexProvider) const;
private:
    std::shared_ptr<Node> root_;
};

}
