#pragma once

#include "record.h"

#include <vector>

namespace bsbi {

class RecordMerger {
public:
    static void merge(const std::vector<std::string>& paths);
};

} // namespace bsbi
