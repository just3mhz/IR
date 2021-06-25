#include "document_reader_iterator.h"

#include <regex>
#include <cassert>
#include <iostream>

namespace document {

const std::regex DocumentReaderIterator::DOC_BEGIN_REGEX{R"(<doc id="(.*)\" url="(.*)\" title="(.*)\">)"};
const std::regex DocumentReaderIterator::DOC_END_REGEX{"</doc>"};

DocumentReaderIterator::DocumentReaderIterator()
    : documentsStream_()
{
}

DocumentReaderIterator::DocumentReaderIterator(std::ifstream& is)
    : documentsStream_(is)
{
    assert(is.is_open());

    auto documentPtr = std::make_shared<Document>();

    std::string docBegin;
    if (!std::getline(documentsStream_->get(), docBegin, '\n'))
        throw std::runtime_error("Unexpected EOF");

    if (docBegin == "</documents>")
        return;

    std::smatch match;
    if (!std::regex_match(docBegin, match, DOC_BEGIN_REGEX))
        throw std::runtime_error("First line doesn't match with DOC_BEGIN_REGEX");
    documentPtr->id() = std::stoi(match[1]);
    documentPtr->url() = match[2];
    documentPtr->title() = match[3];

    bool docEndReached = false;
    std::string currentLine;
    while(std::getline(documentsStream_->get(), currentLine, '\n')) {
        if (std::regex_match(currentLine, DOC_END_REGEX)) {
            docEndReached = true;
            break;
        }
        documentPtr->text() += currentLine;
    }
    if (!docEndReached) {
        throw std::runtime_error("Last line doesn't match with DOC_BEGIN_REGEX");
    }

    documentPtr_ = std::move(documentPtr);
}

DocumentReaderIterator::DocumentReaderIterator(const DocumentReaderIterator& it)
    : documentPtr_(it.documentPtr_)
    , documentsStream_(it.documentsStream_)
{
}

bool DocumentReaderIterator::operator!=(const DocumentReaderIterator& other) const
{
    return documentPtr_ != other.documentPtr_;
}

std::shared_ptr<Document> DocumentReaderIterator::operator*() const
{
    return documentPtr_;
}

DocumentReaderIterator DocumentReaderIterator::operator++()
{
    *this = DocumentReaderIterator(*documentsStream_);
    return *this;
}

}