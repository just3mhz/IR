#pragma once

#include "filter.h"

#include <iostream>

namespace tokenization {

class WordTokenizer {
public:
    virtual std::string tokenize(const std::string& word) const = 0;
};

class SimpleWordTokenizer final: public WordTokenizer {
public:
    SimpleWordTokenizer();
    std::string tokenize(const std::string& word) const override;
private:
    std::shared_ptr<Filter> filter_;
};

}
