#pragma once

#include <iostream>
#include <vector>
#include <memory>

namespace bsbi {

class InvIndexProvider {
public:
    virtual std::vector<std::uint64_t> getDocIds(const std::string& term) const = 0;
};

std::shared_ptr<InvIndexProvider> createInvIndexProvider();

} // namespace bsbi

