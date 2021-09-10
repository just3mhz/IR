#include "posting_list_builder.h"

namespace bsbi::postings {

PostingListBuilder::PostingListBuilder(uint64_t termId)
    : termId_(termId)
{}

uint64_t PostingListBuilder::termId() const
{
    return termId_;
}

void PostingListBuilder::processRecord(const Record& record)
{
    if (record.termId != termId_) {
        std::cerr << "Skipping record " << record << "\n";
        return;
    }

    if (!postings_.contains(record.docId)) {
        postings_.insert({ record.docId, Posting(record.docId) });
        return;
    }

    auto& posting = postings_.at(record.docId);
    posting.count_ += 1;
}

PostingList PostingListBuilder::createPostingList() const
{
    std::vector<Posting> postings;
    postings.reserve(postings_.size());
    for (const auto& [docId, posting]: postings_) {
        postings.push_back(posting);
    }

    std::sort(postings.begin(), postings.end(),
        [](const Posting& lhs, const Posting& rhs) {return lhs.docId_ < rhs.docId(); });

    PostingList postingList(termId_);
    postingList.postings_ = std::move(postings);

    return postingList;
}

} // namespace bsbi::postings