#pragma once

#include "../../common/serialization/serialize.h"

#include <iostream>
#include <map>

namespace bsbi::postings {

class Posting final : public common::serialization::Serializable {
public:

    uint64_t& docId();
    const uint64_t& docId() const;

    uint64_t& count();
    const uint64_t& count() const;

    std::size_t serialize(std::ostream& os) const override;
    std::size_t deserialize(std::istream& is) override;
    std::size_t serialized_size() const noexcept override;
private:
    uint64_t docId_;
    uint64_t count_;
};

} // namespace bsbi::postings