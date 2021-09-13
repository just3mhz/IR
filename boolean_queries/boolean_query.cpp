#include "boolean_query.h"

namespace boolean_query {

using bsbi::postings::Posting;

std::vector<uint64_t> intersect(const std::vector<Posting>& lhs, const std::vector<Posting>& rhs)
{
    std::vector<uint64_t> result;
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < lhs.size() && j < rhs.size()) {
        if (lhs[i].docId() == rhs[j].docId()) {
            result.push_back(lhs[i].docId());
            ++i;
            ++j;
        } else if (lhs[i].docId() < rhs[i].docId()) {
            ++i;
        } else if (lhs[i].docId() > rhs[i].docId()) {
            ++j;
        }
    }
    return result;
}

}
