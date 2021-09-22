#include "tokenization.h"

#include <sstream>
#include <regex>

namespace tokenization {

SimpleTokenizer::SimpleTokenizer()
{
    auto composed = std::make_shared<ComposedFilter>();
    composed->appendFilter(std::make_shared<LowerCaseFilter>());
    composed->appendFilter(std::make_shared<PunctuationFilter>());
    filter_ = std::move(composed);
}

std::vector<std::string> SimpleTokenizer::tokenize(const std::string& content) {
    std::string filteredContent = filter_->apply(content);

    std::vector<std::string> tokens;
    std::string currentToken;
    std::istringstream is(filteredContent);
    while (is >> currentToken) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

} // namespace tokenization