#include "postings/posting.h"

#include "../auxiliary/dictionary.h"

namespace bsbi {

Posting::Posting(const uint64_t termId) : termId_(termId)
{
}

void Posting::pushDocId(const uint64_t docId)
{
    docIds_[docId].count += 1;
}

void Posting::printPosting(std::ostream& os)
{
    const auto& dict = auxiliary::SingletonDictionary::getInstance();

    os << "{ (" << termId_ << ", '" << dict.getTerm(termId_) << "') : [";

    bool first = true;
    for(const auto& [docId, meta]: docIds_) {
        if (!first)
            os << ", ";
        first = false;
        os << "(" << docId << ", " << meta.count << ")";
    }
    os << "] }\n";
}

uint64_t Posting::termId() const
{
    return termId_;
}

}