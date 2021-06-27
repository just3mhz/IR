#include "tokenization.h"

#include <sstream>

namespace tokenization {

namespace {
using Token = std::string;
using Tokens = std::vector<Token>;

Tokens Tokenize(const std::string& content) {
    Tokens tokens;
    Token currentToken;
    std::istringstream is(content);
    while (is >> currentToken) {
        tokens.push_back(currentToken);
    }
    return tokens;
}

} // namespace

TokenizedDocument TokenizeDocument(const document::Document& document) {
    TokenizedDocument result;
    result.doc_id = document.id();
    result.url = document.url();
    result.tokenized_title = Tokenize(document.title());
    result.tokenized_text = Tokenize(document.text());
    return result;
}

}