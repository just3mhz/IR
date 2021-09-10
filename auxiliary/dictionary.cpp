#include "dictionary.h"

#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

namespace auxiliary {

bool SingletonDictionary::hasTerm(const std::string& term) const
{
    return stringToId_.contains(term);
}

const std::string& SingletonDictionary::getTerm(const uint64_t termId) const
{
    if (termId >= idToString_.size())
        throw std::runtime_error("Non-existing termId");
    return idToString_[termId];
}

uint64_t SingletonDictionary::getTermId(const std::string& term)
{
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
    idToString_.clear();
    stringToId_.clear();
}

void SingletonDictionary::dump(const std::string& path) const
{
    std::ofstream ofs(path);
    assert(ofs.is_open());

    ofs << "{\n";
    for (size_t i = 0; i < idToString_.size(); ++i) {
        ofs << "    \"" << idToString_[i] << "\":" << i;
        if (i != idToString_.size() - 1)
            ofs << ",";
        ofs << "\n";
    }
    ofs << "}\n";

    ofs.close();
}

}
