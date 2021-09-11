#pragma once

#include <iostream>

namespace common::serialization {

class Serializable {
public:
    virtual ~Serializable() = default;

    virtual std::size_t serialize(std::ostream& os) const = 0;
    virtual std::size_t deserialize(std::istream& is) = 0;
    virtual std::size_t serializedSize() const noexcept = 0;
};

} // namespace common::serialization
