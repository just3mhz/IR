#pragma once

#include "../../common/serialization/serialize.h"

#include <iostream>
#include <map>

namespace bsbi::postings {

class Posting final : public common::serialization::Serializable {
public:
    Posting() = default;
    explicit Posting(uint64_t docId);

    uint64_t& docId();
    const uint64_t& docId() const;

    uint64_t& count();
    const uint64_t& count() const;

    std::size_t serialize(std::ostream& os) const override;
    std::size_t deserialize(std::istream& is) override;
    std::size_t serializedSize() const noexcept override;
private:
    uint64_t docId_;
    uint64_t count_;

    friend class PostingListBuilder;
};

std::ostream& operator<<(std::ostream& os, const Posting& posting);

} // namespace bsbi::postings