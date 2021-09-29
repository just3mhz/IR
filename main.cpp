#include "bsbi/bsbi.h"

int main() {
    bsbi::BlockedSortBasedIndexer indexer(3);
    indexer.makeIndex("test_data/block01.xml", "test_data/output.bin");
    return 0;
}
