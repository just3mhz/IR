#pragma once

#include "postings/posting_list.h"

#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>

namespace bsbi {

class InvIndexProvider {
public:
    virtual std::vector<std::uint64_t> getDocIds(const std::string& term) const = 0;
    virtual postings::PostingList getPostingList(const uint64_t termId) const = 0;
};

std::shared_ptr<InvIndexProvider> createInvIndexProvider(const std::filesystem::path& indexDir);

} // namespace bsbi

