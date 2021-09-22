#pragma once

#include "filter.h"
#include "../document/document.h"

#include <string>
#include <vector>

namespace tokenization {

class Tokenizer {
public:
    virtual std::vector<std::string> tokenize(const std::string& text) = 0;
};

class SimpleTokenizer final: public Tokenizer {
public:
    SimpleTokenizer();

    std::vector<std::string> tokenize(const std::string& text) override;
private:
    std::shared_ptr<Filter> filter_;
};

} // namespace tokenization
