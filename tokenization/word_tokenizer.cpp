#include "word_tokenizer.h"

namespace tokenization {

SimpleWordTokenizer::SimpleWordTokenizer()
{
    auto filter = std::make_shared<ComposedFilter>();
    filter->appendFilter(std::make_shared<LowerCaseFilter>());
    filter->appendFilter(std::make_shared<PunctuationFilter>());

    filter_ = filter;
}

std::string SimpleWordTokenizer::tokenize(const std::string& word) const
{
    return filter_->apply(word);
}

}