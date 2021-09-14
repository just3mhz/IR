#pragma once

#include <iostream>
#include <regex>
#include <vector>

namespace tokenization {

class Filter {
public:
    virtual std::string apply(const std::string& text) const = 0;
};

class ComposedFilter: public Filter {
public:
    std::string apply(const std::string& text) const override {
        std::string result = text;
        for (const auto& filter: filters_) {
            result = filter->apply(result);
        }
        return result;
    }

    void appendFilter(std::shared_ptr<Filter> filter) {
        filters_.push_back(std::move(filter));
    }

private:
    std::vector<std::shared_ptr<Filter>> filters_;
};

class LowerCaseFilter final: public Filter {
public:
    std::string apply(const std::string& text) const override {
        std::string result = text;
        for(auto& c: result) {
            c = std::tolower(c);
        }
        return result;
    }
};

class PunctuationFilter final: public Filter {
public:
    std::string apply(const std::string& text) const override {
        return std::regex_replace(text, PUNCTUATION_REGEX, " ");
    }

private:
    const static std::regex PUNCTUATION_REGEX;
};

}
