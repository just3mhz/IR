#pragma once

#include "document.h"

#include <fstream>
#include <iterator>
#include <memory>
#include <optional>
#include <regex>


namespace document {

class DocumentReaderIterator : std::iterator<std::forward_iterator_tag, Document> {
    friend class DocumentReader;
public:
    DocumentReaderIterator();
    DocumentReaderIterator(const DocumentReaderIterator& it);

    bool operator!=(DocumentReaderIterator const& other) const;

    std::shared_ptr<Document> operator*() const;
    DocumentReaderIterator operator++();

    const static std::regex DOC_BEGIN_REGEX;
    const static std::regex DOC_END_REGEX;
private:
    explicit DocumentReaderIterator(std::ifstream& is);

    std::shared_ptr<Document> documentPtr_;
    std::optional<std::reference_wrapper<std::ifstream>> documentsStream_;
};

} // namespace document

