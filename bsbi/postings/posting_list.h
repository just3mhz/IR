#pragma once

#include "posting.h"
#include "../../common/serialization/serialize.h"

#include <vector>

namespace bsbi::postings {

class PostingList final : common::serialization::Serializable {
public:
    explicit PostingList(uint64_t termId);

    std::size_t serialize(std::ostream& os) const override;
    std::size_t deserialize(std::istream& is) override;
    std::size_t serialized_size() const noexcept override;

    uint64_t termId() const;

    const std::vector<Posting>& rawPostings() const;
private:
    uint64_t termId_;
    std::vector<Posting> postings_;

    friend class PostingListBuilder;
};

std::ostream& operator<<(std::ostream& os, const PostingList& postingList);

} // namespace bsbi::postings

