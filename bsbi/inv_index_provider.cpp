#include "inv_index_provider.h"
#include "../common/utils.h"

#include <filesystem>
#include <fstream>
#include <unordered_map>

namespace bsbi {

namespace {

class InvIndexProviderImpl final: public InvIndexProvider {
public:
    explicit InvIndexProviderImpl(const std::filesystem::path& indexDir) {
        common::throwIf(!std::filesystem::exists(indexDir),
            "Specified indexDir does not exist");
        common::throwIf(!std::filesystem::is_directory(indexDir),
            "Specified indexDir is not directory");

        std::filesystem::path postingsPath = indexDir / "postings.bin";
        common::throwIf(!std::filesystem::exists(postingsPath),
            "Can not find postings.bin in indexDir");

        std::filesystem::path offsetsPath = indexDir / "offsets.bin";
        common::throwIf(!std::filesystem::exists(postingsPath),
                        "Can not find offsets.bin in indexDir");

        postingsIfs_ = std::ifstream(postingsPath);

        std::ifstream offsetsIfs(offsetsPath);
        uint64_t termId;
        std::size_t offset;
        while (common::serialization::read(offsetsIfs, termId) != 0
               && common::serialization::read(offsetsIfs, offset) != 0) {
            offsets_[termId] = offset;
        }
    }

    std::vector<uint64_t> getDocIds(const std::string& term) const override {
        return {};
    }

    postings::PostingList getPostingList(const uint64_t termId) const override {
        if (!offsets_.contains(termId))
            return {};
        postingsIfs_.seekg(offsets_.at(termId));

        postings::PostingList postingList;
        postingList.deserialize(postingsIfs_);
        return postingList;
    }

private:
    mutable std::ifstream postingsIfs_;
    std::unordered_map<uint64_t, std::size_t> offsets_;
};

} // namespace

std::shared_ptr<InvIndexProvider> createInvIndexProvider(const std::filesystem::path& indexDir) {
    return std::make_shared<InvIndexProviderImpl>(indexDir);
}

}