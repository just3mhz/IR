#include "dictionary.h"

namespace auxiliary {

bool SingletonDictionary::hasTerm(const std::string& term) const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return dict_.count(term) != 0;
}

uint64_t SingletonDictionary::getTermId(const std::string& term)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!dict_.contains(term))
        return (dict_[term] = dict_.size());
    return dict_[term];
}

}
