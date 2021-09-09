#pragma once

#include <iostream>

namespace common::serialization {

class Serializable {
public:
    virtual ~Serializable() = default;

    virtual auto serialize(std::ostream& os) const -> std::size_t = 0;
    virtual auto deserialize(std::istream& is) -> std::size_t = 0;
    virtual auto serialized_size() const noexcept -> std::size_t = 0;
};

template <class T>
auto write(std::ostream& os, const T& value) -> std::size_t
{
    const auto pos = os.tellp();
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
    return static_cast<std::size_t>(os.tellp() - pos);
}

template <>
auto write(std::ostream& os, const bool& value) -> std::size_t
{
    constexpr auto t_value = static_cast<std::uint8_t>('T');
    constexpr auto f_value = static_cast<std::uint8_t>('F');

    const auto pos = os.tellp();
    const auto tmp = (value) ? t_value : f_value;
    os.write(reinterpret_cast<const char*>(&tmp), sizeof(tmp));
    return static_cast<std::size_t>(os.tellp() - pos);
}

template <>
auto write(std::ostream& os, const std::string& value) -> std::size_t
{
    const auto pos = os.tellp();
    const auto len = static_cast<std::uint32_t>(value.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0)
        os.write(value.data(), len);
    return static_cast<std::size_t>(os.tellp() - pos);
}

template <>
auto write(std::ostream& os, const Serializable& value) -> std::size_t
{
    return value.serialize(os);
}

} // namespace common::serialization


