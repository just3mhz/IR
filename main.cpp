#include "bsbi/bsbi.h"

int main() {
    bsbi::BlockedSortBasedIndexer indexer(2);
    indexer.makeIndex(
        "/home/just3mhz/IR/test_data/block01.xml",
        "output.txt");
    return 0;
}
