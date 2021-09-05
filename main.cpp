#include "document/document.h"
#include "document/document_reader.h"
#include "tokenization/tokenization.h"

#include <iostream>

int main() {
    document::DocumentReader reader(
        "/home/just3mhz/IR/test_data/block01.xml",
        10,
        std::make_unique<tokenization::SimpleTokenizer>());
    while (reader) {
        document::Document doc = reader.readNext();
        std::cout << doc << "\n\n";
    }
    return 0;
}
