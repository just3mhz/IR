#include "search_engine.h"


namespace search_engine {

SearchEngine::SearchEngine(std::shared_ptr<bsbi::InvIndexProvider> invIndexProvider)
    : invIndexProvider_(std::move(invIndexProvider))
{}

std::vector<uint64_t> SearchEngine::search(const std::string& query)
{
    auto tokenizedExpression = boolean_queries::tokenizeExpression(query);
    auto rpnExpression = boolean_queries::reversePolishNotation(tokenizedExpression);
    auto expressionTree = boolean_queries::ExpressionTree(rpnExpression);
    return expressionTree.evaluate(*invIndexProvider_);
}

} // namespace search_engine