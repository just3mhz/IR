#pragma once

#include <string>
#include <vector>

namespace bsbi {

struct Record
{
    uint64_t termId{0};
    uint64_t docId{0};

    bool operator==(const Record& other) const {
        return termId == other.termId && docId == other.docId;
    }

    bool operator<(const Record& other) const {
        return termId == other.termId
               ? docId < other.docId
               : termId < other.termId;
    }
};

std::ostream& operator<<(std::ostream& os, const Record& record);

class RecordDumper {
public:
    virtual void dump(const std::string&, const std::vector<Record>&) = 0;
};

class RecordDumperTxt final: public RecordDumper {
public:
    void dump(const std::string&, const std::vector<Record>&) override;
};

class RecordDumperBin final: public RecordDumper {
public:
    void dump(const std::string&, const std::vector<Record>&) override;
};

}