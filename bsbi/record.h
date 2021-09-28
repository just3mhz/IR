#pragma once

#include "../common/serialization/serializable.h"

#include <string>
#include <vector>

namespace bsbi {

struct Record : public common::serialization::Serializable
{
    std::size_t serialize(std::ostream& os) const override;
    std::size_t deserialize(std::istream& is) override;
    std::size_t serializedSize() const noexcept override;

    uint64_t termId{0};
    uint64_t docId{0};
};

bool operator==(const Record& lhs, const Record& rhs) {
    return lhs.docId == rhs.docId && lhs.termId == rhs.termId;
}

bool operator<(const Record& lhs, const Record& rhs) {
    if (lhs.termId == rhs.termId) {
        return lhs.docId < rhs.docId;
    }
    return lhs.termId < rhs.termId;
}

std::ostream& operator<<(std::ostream& os, const Record& record);

}