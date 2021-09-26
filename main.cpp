#include "bsbi/inv_index_provider.h"
#include "search_engine/search_engine.h"

class MockInvertedIndexProvider: public bsbi::InvIndexProvider {
    std::vector<std::uint64_t> getDocIds(const std::string &term) const override {
        if (term == "abc") {
            return {1, 3, 6, 8, 9};
        } else if (term == "cd") {
            return {1, 5, 8};
        } else {
            return {1, 3, 6, 7};
        }
    }
};

int main() {
    search_engine::SearchEngine engine(std::make_shared<MockInvertedIndexProvider>());
    std::string query;
    while (std::getline(std::cin, query, '\n')) {
        auto searchResult = engine.search(query);
        for(const auto& docId: searchResult) {
            std::cout << docId << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}
