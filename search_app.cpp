#include "search_engine/search_engine.h"

#include <filesystem>

int main() {
    auto invIndexProvider = bsbi::createInvIndexProvider("./result");
    search_engine::SearchEngine searchEngine(invIndexProvider);

    std::string query;
    while (std::getline(std::cin, query, '\n')) {
        for(const auto& docId: searchEngine.search(query)) {
            std::cout << docId << ' ';
        }
        std::cout << std::endl;
    }
}