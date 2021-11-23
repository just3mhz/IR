#include "search_engine.h"

#include "../common/handler.h"

namespace search_engine {

SearchEngine::SearchEngine(std::shared_ptr<bsbi::InvIndexProvider> invIndexProvider)
    : invIndexProvider_(std::move(invIndexProvider))
    , wordTokenizer_(std::make_shared<tokenization::SimpleWordTokenizer>())
{}

std::vector<uint64_t> SearchEngine::search(const std::string& query)
{
    common::PerformanceHandler handler("search");
    auto tokenizedExpression = boolean_queries::tokenizeExpression(query, *wordTokenizer_);
    auto rpnExpression = boolean_queries::reversePolishNotation(tokenizedExpression);
    auto expressionTree = boolean_queries::ExpressionTree(rpnExpression);
    return expressionTree.evaluate(*invIndexProvider_);
}

} // namespace search_engine