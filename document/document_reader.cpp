#include "document_reader.h"

#include <cassert>

namespace document {

DocumentReader::DocumentReader(const std::string& filename)
    : documentsStream_()
{
    documentsStream_.open(filename);
    assert(documentsStream_.is_open());
    std::string line;
    std::getline(documentsStream_, line, '\n');
    assert(line == "<documents>");
}

DocumentReaderIterator DocumentReader::begin()
{
    return DocumentReaderIterator(documentsStream_);
}

DocumentReaderIterator DocumentReader::end()
{
    return DocumentReaderIterator();
}

DocumentReader::~DocumentReader() {
    documentsStream_.close();
}

}