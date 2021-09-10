#pragma once

#include "posting.h"
#include "posting_list.h"
#include "../record.h"

#include <unordered_map>

namespace bsbi::postings {

class PostingListBuilder {
public:
    explicit PostingListBuilder(uint64_t termId);

    uint64_t termId() const;

    void processRecord(const Record& record);

    PostingList createPostingList() const;
private:
    uint64_t termId_;
    std::unordered_map<uint64_t, Posting> postings_;
};

} // namespace bsbi::postings

