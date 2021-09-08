#include "dictionary.h"

#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

namespace auxiliary {

bool SingletonDictionary::hasTerm(const std::string& term) const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return stringToId_.contains(term);
}

const std::string& SingletonDictionary::getTerm(const uint64_t termId) const
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (termId >= idToString_.size())
        throw std::runtime_error("Non-existing termId");
    return idToString_[termId];
}

uint64_t SingletonDictionary::getTermId(const std::string& term)
{
    std::lock_guard<std::mutex> lock(mutex_);
    uint64_t termId = idToString_.size();
    if (!stringToId_.contains(term)) {
        idToString_.push_back(term);
        stringToId_[term] = termId;
    } else {
        termId = stringToId_[term];
    }
    return termId;
}

void SingletonDictionary::clear()
{
    std::lock_guard lock(mutex_);
    idToString_.clear();
    stringToId_.clear();
}

void SingletonDictionary::dump(const std::string& path) const
{
    std::ofstream ofs(path);
    assert(ofs.is_open());

    auto records = [this]() -> std::vector<std::pair<std::string, uint64_t>> {
        std::lock_guard lock(mutex_);
        return { stringToId_.begin(), stringToId_.end()};
    }();

    std::sort(records.begin(), records.end());

    ofs << "{\n";
    for (size_t i = 0; i < records.size(); ++i) {
        ofs << "    \"" << records[i].first << "\":" << records[i].second;
        if (i != records.size() - 1)
            ofs << ",";
        ofs << "\n";
    }
    ofs << "}\n";

    ofs.close();
}

}
