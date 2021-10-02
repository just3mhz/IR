#pragma once

#include <filesystem>
#include <optional>

void initLogging(const std::optional<std::filesystem::path>& logPath = std::nullopt);
