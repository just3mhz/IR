#include "posting_list_builder.h"

#include <algorithm>

namespace bsbi::postings {

PostingList PostingListBuilder::makePostingList(uint64_t termId, std::vector<uint64_t> docIds)
{
    PostingList pList(termId);

    if (docIds.empty())
        return pList;

    std::sort(docIds.begin(), docIds.end());
    pList.postings_.emplace_back(docIds[0]);
    for(int i = 1; i < docIds.size(); ++i) {
        if (docIds[i] == docIds[i - 1])
            continue;
        pList.postings_.emplace_back(docIds[i]);
    }

    return pList;
}

} // namespace bsbi::postings