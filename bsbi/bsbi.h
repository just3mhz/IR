#pragma once

#include "../tokenization/tokenization.h"
#include "../auxiliary/dictionary.h"

#include <iostream>
#include <vector>

namespace bsbi {

struct Record
{
    uint64_t termId;
    uint64_t docId;

    bool operator==(const Record& other) const {
        return termId == other.termId && docId == other.docId;
    }
};

template<class Iterator>
std::vector<Record> invertedIndexForBlock(Iterator begin, Iterator end)
{
    std::vector<Record> records;
    auto& dict = auxiliary::SingletonDictionary::getInstance();
    for(Iterator it = begin; it != end; ++it) {
        const tokenization::TokenizedDocument& doc = *it;
        for(const std::string& term: doc.tokenizedTitle)
            records.push_back({dict.getTermId(term), doc.docId});
        for(const std::string& term: doc.tokenizedText)
            records.push_back({dict.getTermId(term), doc.docId});
    }
    return records;
}

}
