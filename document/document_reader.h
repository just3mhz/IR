#pragma once

#include "../tokenization/tokenization.h"

#include <regex>
#include <fstream>
#include <vector>

namespace document {

class DocumentReader {
    using Tokenizer = tokenization::Tokenizer;
public:
    const static std::regex DOC_BEGIN_REGEX;
    const static std::regex DOC_END_REGEX;

    DocumentReader(const std::string& filename, std::size_t bufferSize, Tokenizer* tokenizer);

    bool allDocsRead() const;
    explicit operator bool() const;

    Document&& readNext() const;

    ~DocumentReader();
private:
    void readNextBlockIntoBuffer() const;
    bool readNextDocIntoBuffer() const;

    mutable std::ifstream documentsStream_;

    std::size_t bufferSize_;

    mutable std::vector<Document> buffer_;
    mutable std::vector<Document>::iterator it_;
    mutable bool allDocsRead_{false};

    Tokenizer* tokenizer_;
};

} // namespace document
