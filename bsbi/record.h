#pragma once

#include "../common/serialization/serializable.h"

#include <string>
#include <vector>

namespace bsbi {

struct Record : public common::serialization::Serializable
{
    Record() = default;
    Record(uint64_t termId, uint64_t docId);

    std::size_t serialize(std::ostream& os) const override;
    std::size_t deserialize(std::istream& is) override;
    std::size_t serializedSize() const noexcept override;

    uint64_t termId{0};
    uint64_t docId{0};
};

bool operator==(const Record& lhs, const Record& rhs);
bool operator<(const Record& lhs, const Record& rhs);

std::ostream& operator<<(std::ostream& os, const Record& record);

}