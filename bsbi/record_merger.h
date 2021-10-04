#pragma once

#include "record.h"

#include <vector>
#include <filesystem>

namespace bsbi {

class RecordMerger {
public:
    static void merge(
        const std::vector<std::filesystem::path>& inputPaths,
        const std::filesystem::path& outputPath);
};

} // namespace bsbi
