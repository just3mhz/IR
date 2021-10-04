#include "expression_tree.h"

#include "../common/utils.h"
#include "set_operations.h"

namespace boolean_queries {

namespace {

class OperatorNode final: public Node {
public:
    explicit OperatorNode(const std::shared_ptr<Token>& token) {
        operator_ = std::dynamic_pointer_cast<Operator>(token);
        common::throwIf(operator_ == nullptr, "Can't downcast Token to Operator");
    }

    std::vector<uint64_t> evaluate(const bsbi::InvIndexProvider& invertedIndexProvider) const override {
        std::vector<uint64_t> resultLeft = left_->evaluate(invertedIndexProvider);
        std::vector<uint64_t> resultRight = right_->evaluate(invertedIndexProvider);

        switch (operator_->operatorType()) {
        case Operator::Type::AND:
            return sortedIntersect(resultLeft, resultRight);
        case Operator::Type::OR:
            return sortedJoin(resultLeft, resultRight);
        }

        throw std::runtime_error("Unknown Operator::Type");
    }

    const std::shared_ptr<Node>& left() const override {
        return left_;
    }

    const std::shared_ptr<Node>& right() const override {
        return right_;
    }

    void setLeft(std::shared_ptr<Node> left) override {
        left_ = std::move(left);
    }

    void setRight(std::shared_ptr<Node> right) override {
        right_ = std::move(right);
    }
private:
    std::shared_ptr<Operator> operator_;
    std::shared_ptr<Node> left_;
    std::shared_ptr<Node> right_;
};

class TermNode final: public Node {
public:
    explicit TermNode(const std::shared_ptr<Token>& token) {
        term_ = std::dynamic_pointer_cast<Term>(token);
        common::throwIf(term_ == nullptr, "Can't downcast Token to Term");
    }

    std::vector<uint64_t> evaluate(const bsbi::InvIndexProvider& invertedIndexProvider) const override {
        return invertedIndexProvider.getDocIds(term_->term());
    }

    const std::shared_ptr<Node>& left() const override {
        return nullptr;
    }

    const std::shared_ptr<Node>& right() const override {
        return nullptr;
    }

    void setLeft(std::shared_ptr<Node> left) override {
        throw std::runtime_error("Attempt to set child node for leaf");
    }

    void setRight(std::shared_ptr<Node> right) override {
        throw std::runtime_error("Attempt to set child node for leaf");
    }
private:
    std::shared_ptr<Term> term_;
};


class TreeBuilder {
    using Iterator = std::vector<std::shared_ptr<Token>>::const_reverse_iterator;
public:
    TreeBuilder(const Iterator& begin, const Iterator& end)
        : current_(begin)
        , end_(end)
    {}

    std::shared_ptr<Node> constructTree()
    {
        if (current_ == end_) {
            return nullptr;
        }

        const auto token = *current_;
        current_++;

        std::shared_ptr<Node> node = nullptr;
        switch (token->tokenType()) {
        case TokenType::TERM:
            node = std::make_shared<TermNode>(token);
            break;
        case TokenType::OPERATOR:
            node = std::make_shared<OperatorNode>(token);
            node->setLeft(constructTree());
            node->setRight(constructTree());
            break;
        default:
            throw std::runtime_error("Unexpected token");
        }

        return node;
    }
private:
    Iterator current_;
    Iterator end_;
};

} // namespace

ExpressionTree::ExpressionTree(const std::vector<std::shared_ptr<Token>>& tokens)
{
    auto builder = TreeBuilder(tokens.rbegin(), tokens.rend());
    root_ = builder.constructTree();
}

std::vector<uint64_t> ExpressionTree::evaluate(const bsbi::InvIndexProvider& invertedIndexProvider) const
{
    return root_->evaluate(invertedIndexProvider);
}

} // namespace boolean_queries