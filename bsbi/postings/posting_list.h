#pragma once

#include "posting.h"
#include "../../common/serialization/serialize.h"

#include <vector>

namespace bsbi::postings {

class PostingList final : common::serialization::Serializable {
public:
    std::size_t serialize(std::ostream& os) const override;
    std::size_t deserialize(std::istream& is) override;
    std::size_t serialized_size() const noexcept override;
private:
    uint64_t termId_;
    std::vector<Posting> postings_;
};

} // namespace bsbi::postings


