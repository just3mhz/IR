#include "dictionary.h"

#include <fstream>
#include <vector>
#include <algorithm>

namespace auxiliary {

bool SingletonDictionary::hasTerm(const std::string& term) const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return dict_.contains(term);
}

uint64_t SingletonDictionary::getTermId(const std::string& term)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!dict_.contains(term))
        return (dict_[term] = dict_.size());
    return dict_[term];
}

void SingletonDictionary::clear()
{
    std::lock_guard lock(mutex_);
    dict_.clear();
}

void SingletonDictionary::dump(const std::string& path) const
{
    std::ofstream ofs(path);
    assert(ofs.is_open());

    auto records = [this]() -> std::vector<std::pair<std::string, uint64_t>> {
        std::lock_guard lock(mutex_);
        return {dict_.begin(), dict_.end()};
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
