#include "posting.h"

#include "../../auxiliary/dictionary.h"

namespace bsbi::postings {

Posting::Posting(uint64_t docId)
    : docId_(docId)
    , count_(1)
{
}

uint64_t& Posting::docId()
{
    return docId_;
}

const uint64_t& Posting::docId() const
{
    return docId_;
}

uint64_t& Posting::count()
{
    return count_;
}

const uint64_t& Posting::count() const
{
    return count_;
}

std::size_t Posting::serialize(std::ostream& os) const
{
    const auto pos = os.tellp();
    common::serialization::write(os, docId_);
    common::serialization::write(os, count_);
    return static_cast<std::size_t>(os.tellp() - pos);
}

std::size_t Posting::deserialize(std::istream& is)
{
    const auto pos = is.tellg();
    common::serialization::read(is, docId_);
    common::serialization::read(is, count_);
    return static_cast<std::size_t>(is.tellg() - pos);
}

std::size_t Posting::serialized_size() const noexcept
{
    return sizeof(docId_) + sizeof(count_);
}

std::ostream& operator<<(std::ostream& os, const Posting& posting)
{
    os << "(docId=" << posting.docId() << ", count=" << posting.count() << ")";
    return os;
}

}