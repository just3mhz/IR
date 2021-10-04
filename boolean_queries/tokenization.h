#pragma once

#include "token.h"

#include <vector>
#include <memory>

namespace boolean_queries {

std::vector<std::shared_ptr<Token>> tokenizeExpression(const std::string& rawExpression);

} // namespace boolean_queries
