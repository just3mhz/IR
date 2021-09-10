#include "posting_list.h"

namespace bsbi::postings {

std::size_t PostingList::serialize(std::ostream& os) const
{
    const auto pos = os.tellp();
    common::serialization::write(os, termId_);
    common::serialization::write(os, postings_.size());
    for (const auto& posting: postings_) {
        common::serialization::write(os, posting);
    }
    return static_cast<std::size_t>(os.tellp() - pos);
}

std::size_t PostingList::deserialize(std::istream& is)
{
    const auto pos = is.tellg();

    common::serialization::read(is, termId_);

    std::size_t len;
    common::serialization::read(is, len);

    postings_ = std::vector<Posting>(len);
    for (std::size_t i = 0; i < len; ++i) {
        postings_[i].deserialize(is);
    }

    return static_cast<std::size_t>(is.tellg() - pos);
}

std::size_t PostingList::serialized_size() const noexcept
{
    std::size_t bytes = sizeof(termId_);
    bytes += sizeof(postings_.size());
    for (const auto& posting: postings_) {
        bytes += posting.serialized_size();
    }
    return bytes;
}

}