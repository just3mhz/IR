#include "search_engine/search_engine.h"
#include "document/document_index.h"

#include <filesystem>

const std::string URL_PREFIX{"https://en.wikisource.org/wiki"};

int main() {
    auto invIndexProvider = bsbi::createInvIndexProvider("./result");
    auto documentIndex = document::createDocumentIndex("./result/document_index.bin");

    search_engine::SearchEngine searchEngine(invIndexProvider);

    std::string query;
    while (std::getline(std::cin, query, '\n')) {
        int resultsPrinted = 0;
        for(const auto& docId: searchEngine.search(query)) {
            std::cout << docId << ' ' << URL_PREFIX + documentIndex->url(docId) << '\n';
            resultsPrinted += 1;
            if (resultsPrinted > 10) {
                break;
            }
        }
    }
}