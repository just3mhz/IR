#pragma once

#include "../../common/serialization/serialize.h"

#include <iostream>
#include <map>

namespace bsbi::postings {

struct Posting final : public common::serialization::Serializable {
public:
    Posting() = default;
    explicit Posting(uint64_t docId);

    std::size_t serialize(std::ostream& os) const override;
    std::size_t deserialize(std::istream& is) override;
    std::size_t serializedSize() const noexcept override;

    uint64_t docId{0};
};

std::ostream& operator<<(std::ostream& os, const Posting& posting);

} // namespace bsbi::postings