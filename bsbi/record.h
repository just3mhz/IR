#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

namespace bsbi {

struct Record
{
    uint64_t termId;
    uint64_t docId;

    bool operator==(const Record& other) const {
        return termId == other.termId && docId == other.docId;
    }
};

std::ostream& operator<<(std::ostream& os, const Record& record);

std::istream& operator>>(std::istream& is, Record& record);


template <class Stream>
class RecordReader {
public:
    RecordReader(Stream, size_t);

    Record& record();
    const Record& record() const;

private:
    void readNextBlock();

    Stream inputStream_;

    std::size_t bufferSize_;
    std::vector<Record> buffer_;
    std::vector<Record>::iterator it_;
};

template class RecordReader<std::ifstream>;
template class RecordReader<std::istringstream>;

} // namespace bsbi

