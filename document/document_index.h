#pragma once

#include "document.h"
#include "../common/serialization/serializable.h"

#include <memory>
#include <filesystem>

namespace document {

class DocumentIndex: public common::serialization::Serializable {
public:
    virtual void appendDocument(const Document& document) = 0;
    virtual void removeDocument(const uint64_t docId) = 0;

    virtual const std::string& url(const uint64_t docId) const = 0;

    virtual ~DocumentIndex() = default;
};

std::shared_ptr<DocumentIndex> createDocumentIndex();
std::shared_ptr<DocumentIndex> createDocumentIndex(const std::filesystem::path& indexPath);

}
