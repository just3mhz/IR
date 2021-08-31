#include "dictionary.h"

namespace auxiliary {

bool HashDictionary::hasTerm(const std::string& term)
{
    return dict_.count(term) != 0;
}

void HashDictionary::addTerm(const std::string& term)
{
    if (hasTerm(term))
        throw std::runtime_error("Attempt to add existing term to dictionary");
    uint64_t termId = dict_.size();
    dict_.emplace(term, termId);
}

uint64_t HashDictionary::getTermId(const std::string& term)
{
    if (!hasTerm(term))
        throw std::runtime_error("Attempt to add existing term to dictionary");
    return dict_[term];
}

}
