#include "posting.h"

namespace bsbi::postings {


Posting::Posting(uint64_t docId)
    : docId(docId)
{}

std::size_t Posting::serialize(std::ostream& os) const
{
    const auto pos = os.tellp();
    common::serialization::write(os, docId);
    return static_cast<std::size_t>(os.tellp() - pos);
}

std::size_t Posting::deserialize(std::istream& is)
{
    const auto pos = is.tellg();
    common::serialization::read(is, docId);
    return static_cast<std::size_t>(is.tellg() - pos);
}

std::size_t Posting::serializedSize() const noexcept
{
    return sizeof(docId);
}

std::ostream& operator<<(std::ostream& os, const Posting& posting)
{
    os << "Posting(docId=" << posting.docId << ")";
    return os;
}

} // namespace bsbi::postings