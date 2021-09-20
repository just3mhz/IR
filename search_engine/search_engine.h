#pragma once

#include <vector>

namespace search_engine {

class SearchEngine {
public:
    virtual std::vector<uint64_t> search(const std::string& query) = 0;
};

} // namespace search_engine
