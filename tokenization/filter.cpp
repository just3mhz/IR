#include "filter.h"


namespace tokenization {

const std::regex PunctuationFilter::PUNCTUATION_REGEX(R"([,|.|?|!|"|'|-])");

} // namespace tokenization