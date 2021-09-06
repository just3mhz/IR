#pragma once

#include "../document/document.h"

#include <string>
#include <vector>

namespace tokenization {

class Tokenizer {
public:
    virtual std::vector<std::string> tokenize(const std::string& text) = 0;
};

class SimpleTokenizer final: public Tokenizer {
    std::vector<std::string> tokenize(const std::string& text) override;
};

} // namespace tokenization