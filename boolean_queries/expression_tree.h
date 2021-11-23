#pragma once

#include "token.h"
#include "../bsbi/inv_index_provider.h"

#include <vector>
#include <memory>

namespace boolean_queries {

class Node {
public:
    virtual std::vector<uint64_t> evaluate(const bsbi::InvIndexProvider& invertedIndexProvider) const = 0;
    virtual const std::shared_ptr<Node>& left() const = 0;
    virtual const std::shared_ptr<Node>& right() const = 0;
    virtual void setLeft(std::shared_ptr<Node> left) = 0;
    virtual void setRight(std::shared_ptr<Node> right) = 0;
    virtual int childNum() const = 0;
};

class ExpressionTree {
public:
    ExpressionTree() = default;
    explicit ExpressionTree(const std::vector<std::shared_ptr<Token>>& tokens);

    std::vector<uint64_t> evaluate(const bsbi::InvIndexProvider& invertedIndexProvider) const;
private:
    std::shared_ptr<Node> root_;
};

}
