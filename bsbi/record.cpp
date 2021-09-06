#include "record.h"

#include <fstream>
#include <cassert>

namespace bsbi {

void RecordDumperTxt::dump(const std::string& filepath, const std::vector<Record>& records)
{
    std::ofstream ofs(filepath);
    assert(ofs.is_open());

    ofs << records.size() << '\n';
    for(const auto& record: records) {
        ofs << record.termId << ' ' << record.docId << '\n';
    }

    ofs.close();
}

void RecordDumperBin::dump(const std::string& filepath, const std::vector<Record>& records)
{
    std::ofstream ofs(filepath, std::ios::binary);
    assert(ofs.is_open());

    std::size_t size = records.size();
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& record: records) {
        ofs.write(reinterpret_cast<const char*>(&record.termId), sizeof(record.termId));
        ofs.write(reinterpret_cast<const char*>(&record.docId), sizeof(record.docId));
    }
    ofs.close();
}

}