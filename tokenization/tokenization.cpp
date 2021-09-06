#include "tokenization.h"

#include <sstream>

namespace tokenization {

std::vector<std::string> SimpleTokenizer::tokenize(const std::string& content) {
    std::vector<std::string> tokens;

    std::string currentToken;
    std::istringstream is(content);
    while (is >> currentToken) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

} // namespace tokenization