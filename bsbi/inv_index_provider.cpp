#include "inv_index_provider.h"

#include <filesystem>

namespace bsbi {

namespace {

class InvIndexProviderImpl final: public InvIndexProvider {
public:
    std::vector<uint64_t> getDocIds(const std::string& term) const override {
        return {};
    }
};

} // namespace

std::shared_ptr<InvIndexProvider> createInvIndexProvider() {
    return std::make_shared<InvIndexProviderImpl>();
}

}