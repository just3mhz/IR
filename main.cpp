#include "bsbi/bsbi.h"

int main() {
    bsbi::BlockedSortBasedIndexer indexer(2);
    indexer.makeIndex(
        "test_data/block01.xml",
        "output.txt");
    return 0;
}
