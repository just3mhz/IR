#pragma once

#include "posting.h"
#include "posting_list.h"
#include "../record.h"

#include <unordered_map>

namespace bsbi::postings {

class PostingListBuilder {
public:
    static PostingList makePostingList(uint64_t termId, std::vector<uint64_t> docId);
};

} // namespace bsbi::postings

