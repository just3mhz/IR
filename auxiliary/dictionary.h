#pragma once

#include <iostream>
#include <unordered_map>

namespace auxiliary {

class Dictionary {
    virtual bool hasTerm(const std::string&) = 0;
    virtual void addTerm(const std::string&) = 0;
    virtual uint64_t getTermId(const std::string&) = 0;
};

class HashDictionary final : Dictionary {
public:
    HashDictionary() = default;

    bool hasTerm(const std::string&) override;
    void addTerm(const std::string&) override;
    uint64_t getTermId(const std::string&) override;

private:
    std::unordered_map<std::string, uint64_t> dict_;
};

}