#include "set_operations.h"

namespace boolean_queries {

std::vector<uint64_t> sortedIntersect(const std::vector<uint64_t>& lhs, const std::vector<uint64_t>& rhs)
{
    std::vector<uint64_t> result;
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < lhs.size() && j < rhs.size()) {
        if (lhs[i] == rhs[j]) {
            result.push_back(lhs[i]);
            ++i;
            ++j;
        } else if (lhs[i] < rhs[j]) {
            ++i;
        } else if (lhs[i] > rhs[j]) {
            ++j;
        }
    }
    return result;
}

std::vector<uint64_t> sortedJoin(const std::vector<uint64_t>& lhs, const std::vector<uint64_t>& rhs)
{
    std::vector<uint64_t> result;
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < lhs.size() && j < rhs.size()) {
        if (lhs[i] < rhs[j]) {
            result.push_back(lhs[i]);
            ++i;
        } else if (lhs[i] > rhs[j]) {
            result.push_back(rhs[j]);
            ++j;
        } else {
            result.push_back(lhs[i]);
            ++i;
            ++j;
        }
    }

    for(; i < lhs.size(); ++i) {
        result.push_back(lhs[i]);
    }

    for(; j < rhs.size(); ++j) {
        result.push_back(rhs[j]);
    }

    return result;
}

std::vector<uint64_t> sortedExcept(const std::vector<uint64_t>& lhs, const std::vector<uint64_t>& rhs)
{
    std::vector<uint64_t> result;
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < lhs.size() && j < rhs.size()) {
        if (lhs[i] < rhs[i]) {
            result.push_back(lhs[i]);
            ++i;
        } else if (lhs[i] > rhs[i]) {
            ++j;
        } else {
            ++i;
            ++j;
        }
    }

    for(; i < lhs.size(); ++i) {
        result.push_back(lhs[i]);
    }

    return result;
}

}
