#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>

namespace bsbi {

class InvIndexProvider {
public:
    virtual std::vector<uint64_t> getDocIds(const std::string& term) const = 0;
    virtual std::vector<uint64_t> getDocIds(const uint64_t termId) const = 0;

    virtual ~InvIndexProvider() = default;
};

std::shared_ptr<InvIndexProvider> createInvIndexProvider(const std::filesystem::path& indexDir);

} // namespace bsbi

