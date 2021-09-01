#pragma once

#include <iostream>
#include <unordered_map>
#include <mutex>

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
    uint64_t getTermId(const std::string&);

protected:
    SingletonDictionary() = default;
private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, uint64_t> dict_;
};

}