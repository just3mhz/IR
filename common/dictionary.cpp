#include "dictionary.h"

#include "serialization/serialize.h"
#include "utils.h"
#include "handler.h"

#include <boost/log/trivial.hpp>

namespace common {

Dictionary::Iterator::Iterator(const std::unordered_map<uint64_t, std::string>::const_iterator& it)
    : it_(it)
{
}

Dictionary::Iterator& Dictionary::Iterator::operator++()
{
    it_++;
    return *this;
}

const std::pair<uint64_t, std::string>& Dictionary::Iterator::operator*() const
{
    return *it_;
}

bool Dictionary::Iterator::operator!=(const Dictionary::Iterator& other) const
{
    return it_ != other.it_;
}

const std::string& Dictionary::at(const uint64_t termId) const
{
    return idToTerm_.at(termId);
}

uint64_t Dictionary::at(const std::string& term) const
{
    return termToId_.at(term);
}

bool Dictionary::contains(const uint64_t termId) const
{
    return idToTerm_.contains(termId);
}

bool Dictionary::contains(const std::string& term) const
{
    return termToId_.contains(term);
}

std::size_t Dictionary::size() const
{
    return idToTerm_.size();
}

void Dictionary::insert(const std::string& term, const uint64_t termId)
{
    if (contains(term)) {
        erase(term);
    }

    if (contains(termId)) {
        erase(termId);
    }

    termToId_.insert({ term, termId });
    idToTerm_.insert({ termId, term });
}

void Dictionary::erase(const std::string& term)
{
    throwIf(!termToId_.contains(term),
        "Attempt to erase non-existing term");
    const uint64_t termId = termToId_.at(term);
    termToId_.erase(term);
    idToTerm_.erase(termId);
}

void Dictionary::erase(const uint64_t termId)
{
    throwIf(!idToTerm_.contains(termId),
        "Attempt to erase non-existing termId");
    const auto term = std::move(idToTerm_.at(termId));
    termToId_.erase(term);
    idToTerm_.erase(termId);
}

Dictionary::Iterator Dictionary::begin() const
{
    return Dictionary::Iterator(idToTerm_.begin());
}

Dictionary::Iterator Dictionary::end() const
{
    return Dictionary::Iterator(idToTerm_.end());
}

std::size_t Dictionary::serialize(std::ostream& os) const
{
    PerformanceHandler handler("serialize_dictionary");
    const auto pos = os.tellp();
    common::serialization::write(os, idToTerm_.size());
    for (const auto& [termId, term] : idToTerm_) {
        common::serialization::write(os, termId);
        common::serialization::write(os, term);
    }
    return static_cast<std::size_t>(os.tellp() - pos);
}

std::size_t Dictionary::deserialize(std::istream& is)
{
    PerformanceHandler handler("deserialize_dictionary");
    const auto pos = is.tellg();
    std::size_t dictSize;
    common::serialization::read(is, dictSize);

    std::unordered_map<std::string, uint64_t> termToId;
    std::unordered_map<uint64_t, std::string> idToTerm;
    for (int i = 0; i < dictSize; ++i) {
        uint64_t termId;
        common::serialization::read(is, termId);

        std::string term;
        common::serialization::read(is, term);

        if (termToId.contains(term) || idToTerm.contains(termId)) {
            BOOST_LOG_TRIVIAL(warning) << "Inconsistent serialized dictionary";
            termToId.erase(term);
            idToTerm.erase(termId);
        }

        termToId.insert({ term, termId });
        idToTerm.insert({ termId, term });
    }

    termToId_ = std::move(termToId);
    idToTerm_ = std::move(idToTerm);

    return static_cast<std::size_t>(is.tellg() - pos);
}

std::size_t Dictionary::serializedSize() const noexcept
{
    auto bytes = sizeof(idToTerm_.size());
    bytes += idToTerm_.size() * sizeof(uint64_t);
    for (const auto& [termId, term] : idToTerm_) {
        bytes += (sizeof(term.size()) + term.size());
    }
    return bytes;
}

}