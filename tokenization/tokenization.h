#pragma once

#include "../document/document.h"

#include <string>
#include <vector>

namespace tokenization {

struct TokenizedDocument {
    std::uint64_t docId;
    std::string url;
    std::vector<std::string> tokenizedTitle;
    std::vector<std::string> tokenizedText;
};

TokenizedDocument tokenizeDocument(const document::Document& document);

} // namespace tokenization