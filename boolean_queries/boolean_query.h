#pragma once

#include "../bsbi/postings/posting.h"

#include <vector>

namespace boolean_query {

std::vector<uint64_t> intersect(
    const std::vector<bsbi::postings::Posting>&,
    const std::vector<bsbi::postings::Posting>&);

} // namespace boolean_query