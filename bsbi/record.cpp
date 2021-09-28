#include "record.h"

#include "../common/serialization/serialize.h"

namespace bsbi {

std::size_t Record::serialize(std::ostream& os) const
{
    const auto pos = os.tellp();
    common::serialization::write(os, termId);
    common::serialization::write(os, docId);
    return static_cast<std::size_t>(os.tellp() - pos);
}

std::size_t Record::deserialize(std::istream& is)
{
    const auto pos = is.tellg();
    common::serialization::read(is, termId);
    common::serialization::read(is, docId);
    return static_cast<std::size_t>(is.tellg() - pos);
}

std::size_t Record::serializedSize() const noexcept
{
    return sizeof(termId) + sizeof(docId);
}

std::ostream& operator<<(std::ostream& os, const Record& record)
{
    os << "(terId=" << record.termId << ", docId=" << record.docId << ")";
    return os;
}

}