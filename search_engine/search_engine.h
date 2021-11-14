#pragma once

#include "../bsbi/inv_index_provider.h"
#include "../boolean_queries/expression_tree.h"
#include "../boolean_queries/parser.h"
#include "../boolean_queries/tokenization.h"
#include "../tokenization/word_tokenizer.h"

namespace search_engine {

class SearchEngine {
public:
    explicit SearchEngine(std::shared_ptr<bsbi::InvIndexProvider>);
    std::vector<uint64_t> search(const std::string& query);
private:
    std::shared_ptr<bsbi::InvIndexProvider> invIndexProvider_;
    std::shared_ptr<tokenization::WordTokenizer> wordTokenizer_;
};

} // namespace search_engine
