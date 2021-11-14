#pragma once

#include "token.h"
#include "../tokenization/word_tokenizer.h"

#include <vector>
#include <memory>

namespace boolean_queries {

std::vector<std::shared_ptr<Token>> tokenizeExpression(
    const std::string& rawExpression,
    const tokenization::WordTokenizer& wordTokenizer);

} // namespace boolean_queries
