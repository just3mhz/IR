#include "posting_list.h"

namespace bsbi::postings {

PostingList::PostingList(uint64_t termId)
    : termId_(termId)
{
}

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

std::size_t PostingList::serializedSize() const noexcept
{
    std::size_t bytes = sizeof(termId_);
    bytes += sizeof(postings_.size());
    for (const auto& posting: postings_) {
        bytes += posting.serializedSize();
    }
    return bytes;
}

uint64_t PostingList::termId() const
{
    return termId_;
}

const std::vector<Posting>& PostingList::rawPostings() const
{
    return postings_;
}

std::ostream& operator<<(std::ostream& os, const PostingList& postingList)
{
    os << "{ " << postingList.termId() << " : [";
    bool first = true;
    for (const auto& posting: postingList.rawPostings()) {
        if (!first)
            os << ", ";
        first = false;
        os << posting;
    }
    os << "] }";
    return os;
}

}