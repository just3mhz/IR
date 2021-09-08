#include "document_reader.h"

#include <cassert>
#include <string>

namespace document {

const std::regex DocumentReader::DOC_BEGIN_REGEX{R"(<doc id="(.*)\" url="(.*)\" title="(.*)\">)"};
const std::regex DocumentReader::DOC_END_REGEX{"</doc>"};

DocumentReader::DocumentReader(const std::string& filename, std::size_t bufferSize, Tokenizer* tokenizer)
    : documentsStream_()
    , bufferSize_(bufferSize)
    , tokenizer_(tokenizer)
{
    documentsStream_.open(filename);
    assert(documentsStream_.is_open());

    buffer_.reserve(bufferSize_);

    std::string line;
    std::getline(documentsStream_, line, '\n');
    assert(line == "<documents>");

    readNextBlockIntoBuffer();
}

bool DocumentReader::allDocsRead() const
{
    return allDocsRead_ && it_ == buffer_.end();
}

DocumentReader::operator bool() const
{
    return !allDocsRead();
}

Document&& DocumentReader::readNext() const
{
    if (allDocsRead())
        throw std::runtime_error("All documents read");

    if (it_ == buffer_.end())
        readNextBlockIntoBuffer();

    return std::move(*(it_++));
}

void DocumentReader::readNextBlockIntoBuffer() const
{
    assert(!allDocsRead_);

    buffer_.clear();
    while (buffer_.size() < bufferSize_) {
        if (!readNextDocIntoBuffer()) {
            allDocsRead_ = true;
            break;
        }
    }
    it_ = buffer_.begin();
}

bool DocumentReader::readNextDocIntoBuffer() const
{
    assert(documentsStream_.is_open());

    Document document;

    std::string docBegin;
    if (!std::getline(documentsStream_, docBegin, '\n')) {
        throw std::runtime_error("Unexpected EOF");
    }

    if (docBegin == "</documents>") {
        return false;
    }

    std::smatch match;
    if (!std::regex_match(docBegin, match, DOC_BEGIN_REGEX)) {
        throw std::runtime_error("First line doesn't match with DOC_BEGIN_REGEX");
    }

    document.id() = std::stoi(match[1]);
    document.url() = match[2];
    document.title() = tokenizer_->tokenize(match[3]);

    bool docEndReached = false;
    std::string currentLine;
    std::string text;
    while(std::getline(documentsStream_, currentLine, '\n')) {
        if (std::regex_match(currentLine, DOC_END_REGEX)) {
            docEndReached = true;
            break;
        }
        text += currentLine + " ";
    }
    document.text() = tokenizer_->tokenize(text);

    if (!docEndReached) {
        throw std::runtime_error("Last line doesn't match with DOC_BEGIN_REGEX");
    }

    buffer_.push_back(document);
    return true;
}

DocumentReader::~DocumentReader() {
    documentsStream_.close();
}

}