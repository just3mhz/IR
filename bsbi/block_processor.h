#pragma once

#include "record.h"
#include "../document/document.h"
#include "../common/dictionary.h"

#include <vector>

namespace bsbi {

class BlockProcessor {
public:
    BlockProcessor() = default;

    template<class Iterator>
    std::vector<Record> processBlock(Iterator begin, Iterator end, size_t threads=1);

    template<class Iterator>
    std::vector<Record> processBlockSingleThread(Iterator begin, Iterator end);

    const common::Dictionary& dictionary() const;
private:
    common::Dictionary dict_;
};

} // namespace bsbi