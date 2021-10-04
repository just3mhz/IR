#pragma once

#include "serialization/serializable.h"

#include <unordered_map>
#include <string>
#include <string_view>

namespace common {

class Dictionary: public serialization::Serializable {
public:
    Dictionary() = default;

    const std::string& at(const uint64_t termId) const;
    uint64_t at(const std::string& term) const;

    bool contains(const uint64_t termId) const;
    bool contains(const std::string& term) const;

    std::size_t size() const;


    void insert(const std::string& term, const uint64_t termId);
    void erase(const std::string& term);
    void erase(const uint64_t termId);

    class Iterator {
    public:
        Iterator& operator++();
        const std::pair<uint64_t, std::string>& operator*() const;
        bool operator!=(const Dictionary::Iterator& other) const;

        friend class Dictionary;
    private:
        Iterator(const std::unordered_map<uint64_t, std::string>::const_iterator& it);
        std::unordered_map<uint64_t, std::string>::const_iterator it_;
    };

    Iterator begin() const;
    Iterator end() const;

    // common::serialization::Serializable
    std::size_t serialize(std::ostream& os) const;
    std::size_t deserialize(std::istream& is);
    std::size_t serializedSize() const noexcept;
private:
    std::unordered_map<std::string, uint64_t> termToId_;
    std::unordered_map<uint64_t, std::string> idToTerm_;
};

} // namespace common