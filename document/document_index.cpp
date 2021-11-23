#include "document_index.h"

#include "../common/handler.h"
#include "../common/serialization/serialize.h"

#include <unordered_map>
#include <fstream>

#include <boost/log/trivial.hpp>

namespace document {

namespace {

class DocumentIndexImpl final: public DocumentIndex {
public:
    void appendDocument(const Document& document) override {
        docs_[document.id()] = {.url=document.url()};
    }

    void removeDocument(const uint64_t docId) override {
        if (docs_.contains(docId)) {
            docs_.erase(docId);
        } else {
            BOOST_LOG_TRIVIAL(warning) << "Attempt to remove non-existing document";
        }
    }

    const std::string& url(const uint64_t docId) const override {
        if (docs_.contains(docId)) {
            return docs_.at(docId).url;
        }
        throw std::runtime_error("Document with id=" + std::to_string(docId) + " not found");
    }

    std::size_t serialize(std::ostream& os) const override {
        common::PerformanceHandler handler("serialize_doc_index");
        const auto pos = os.tellp();
        common::serialization::write(os, docs_.size());
        for (const auto& [docId, metadata] : docs_) {
            common::serialization::write(os, docId);
            common::serialization::write(os, metadata.url);
        }
        return static_cast<std::size_t>(os.tellp() - pos);
    }

    std::size_t deserialize(std::istream& is) override {
        common::PerformanceHandler handler("deserialize_doc_index");
        const auto pos = is.tellg();
        std::size_t docsCount;
        common::serialization::read(is, docsCount);

        std::unordered_map<uint64_t, Metadata> docs;
        for (int i = 0; i < docsCount; ++i) {
            uint64_t docId;
            common::serialization::read(is, docId);

            std::string url;
            common::serialization::read(is, url);

            docs.insert({docId, {.url=url}});
        }

        docs_ = std::move(docs);
        return static_cast<std::size_t>(is.tellg() - pos);
    }

    std::size_t serializedSize() const noexcept override {
        auto bytes = sizeof(docs_.size());
        bytes += docs_.size() * sizeof(uint64_t);
        for (const auto& [docId, metadata] : docs_) {
            bytes += (sizeof(metadata.url.size()) + metadata.url.size());
        }
        return bytes;
    }

    virtual ~DocumentIndexImpl() = default;

private:

    struct Metadata {
        std::string url;
    };

    std::unordered_map<uint64_t, Metadata> docs_;
};

} // namespace

std::shared_ptr<DocumentIndex> createDocumentIndex()
{
    return std::make_shared<DocumentIndexImpl>();
}

std::shared_ptr<DocumentIndex> createDocumentIndex(const std::filesystem::path& indexPath)
{
    std::ifstream documentIndexStream(indexPath);
    assert(documentIndexStream.is_open());

    auto documentIndex = createDocumentIndex();

    common::serialization::read(documentIndexStream, *documentIndex);
    return documentIndex;
}

} // namespace document