#pragma once

#include <iostream>
#include <unordered_map>
#include <mutex>
#include <vector>

namespace auxiliary {

class SingletonDictionary {
public:
    static SingletonDictionary& getInstance() {
        static SingletonDictionary instance;
        return instance;
    }

    SingletonDictionary(const SingletonDictionary&) = delete;
    SingletonDictionary(SingletonDictionary&&) = delete;

    bool hasTerm(const std::string&) const;
    const std::string& getTerm(const uint64_t termId) const;
    uint64_t getTermId(const std::string&);

    void dump(const std::string& path) const;

    void clear();

protected:
    SingletonDictionary() = default;
private:
    std::unordered_map<std::string_view, uint64_t> stringToId_;
    std::vector<std::string> idToString_;
};

}