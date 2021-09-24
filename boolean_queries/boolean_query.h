#pragma once

#include "../bsbi/postings/posting.h"

#include <vector>

namespace boolean_queries {

std::vector<uint64_t> sortedIntersect(
    const std::vector<uint64_t>&,
    const std::vector<uint64_t>&);

std::vector<uint64_t> sortedJoin(
    const std::vector<uint64_t>&,
    const std::vector<uint64_t>&);

} // namespace boolean_query