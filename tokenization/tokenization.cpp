#include "tokenization.h"

#include <sstream>

namespace tokenization {

namespace {
using Token = std::string;
using Tokens = std::vector<Token>;

Tokens tokenize(const std::string& content) {
    Tokens tokens;
    Token currentToken;
    std::istringstream is(content);
    while (is >> currentToken) {
        tokens.push_back(currentToken);
    }
    return tokens;
}

} // namespace

TokenizedDocument tokenizeDocument(const document::Document& document) {
    TokenizedDocument result;
    result.docId = document.id();
    result.url = document.url();
    result.tokenizedTitle = tokenize(document.title());
    result.tokenizedText = tokenize(document.text());
    return result;
}

}