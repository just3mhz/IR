#pragma once

#include "document_reader_iterator.h"

namespace document {

class DocumentReader {
public:
    explicit DocumentReader(const std::string& filename);

    DocumentReaderIterator begin();
    DocumentReaderIterator end();

    ~DocumentReader();
private:
    std::ifstream documentsStream_;
};

} // namespace document
