#pragma once

#include "../document/document.h"

#include <string>
#include <vector>

namespace tokenization {

struct TokenizedDocument {
    std::uint64_t doc_id;
    std::string url;
    std::vector<std::string> tokenized_title;
    std::vector<std::string> tokenized_text;
};

TokenizedDocument TokenizeDocument(const document::Document& document);

} // namespace tokenization