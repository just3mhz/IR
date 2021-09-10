#pragma once

#include <iostream>
#include <map>

namespace bsbi {

class Posting {
public:
    struct MetaInf {
        uint64_t count{0};
    };

    explicit Posting(uint64_t termId);

    void pushDocId(uint64_t docId);
    void printPosting(std::ostream& os);

    uint64_t termId() const;

private:
    uint64_t termId_;
    std::map<uint64_t, MetaInf> docIds_;
};


}