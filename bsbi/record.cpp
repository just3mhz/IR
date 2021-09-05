#include "record.h"

namespace bsbi {

std::ostream& operator<<(std::ostream& os, const Record& record)
{
    return (os << '(' << record.termId << ", " << record.docId << ')');
}

std::istream& operator>>(std::istream& is, Record& record)
{
    return (is >> record.termId >> record.docId);
}

template <class Stream>
RecordReader<Stream>::RecordReader(Stream inputStream, size_t bufferSize)
    : inputStream_(std::move(inputStream))
    , bufferSize_(bufferSize)
{
    buffer_.reserve(bufferSize_);
    readNextBlock();
}

template <class Stream>
Record& RecordReader<Stream>::operator*()
{
    return *it_;
}

template <class Stream>
void RecordReader<Stream>::readNextBlock() {
    buffer_.clear();

    Record record{};
    while (buffer_.size() < bufferSize_ && inputStream_ >> record) {
        buffer_.push_back(record);
    }

    it_ = buffer_.begin();
}

}