#pragma once

#include "token.h"

#include <iostream>
#include <memory>
#include <stack>
#include <vector>

namespace boolean_queries {

std::vector<std::shared_ptr<Token>> reversePolishNotation(const std::vector<std::shared_ptr<Token>>& tokens);

} // namespace boolean_queries