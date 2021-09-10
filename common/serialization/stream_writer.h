#pragma once

#include "serializable.h"

#include <iostream>

namespace common::serialization {

template <class T, class U = void>
class StreamWriter {
public:
    static std::size_t write(std::ostream& os, const T& value)
    {
        const auto pos = os.tellp();
        os.write(reinterpret_cast<const char*>(&value), sizeof(value));
        return static_cast<std::size_t>(os.tellp() - pos);
    }
};

template <>
class StreamWriter<bool> {
public:
    static std::size_t write(std::ostream& os, const bool& value)
    {
        const auto pos = os.tellp();
        const auto tmp = (value) ? t_value : f_value;
        os.write(reinterpret_cast<const char*>(&tmp), sizeof(tmp));
        return static_cast<std::size_t>(os.tellp() - pos);
    }
private:
    static constexpr auto t_value = static_cast<std::uint8_t>('T');
    static constexpr auto f_value = static_cast<std::uint8_t>('F');
};

template <>
class StreamWriter<std::string> {
public:
    static std::size_t write(std::ostream& os, const std::string& value)
    {
        const auto pos = os.tellp();
        const auto len = static_cast<std::uint32_t>(value.size());
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        if (len > 0)
            os.write(value.data(), len);
        return static_cast<std::size_t>(os.tellp() - pos);
    }
};

template <class T>
class StreamWriter<T, std::enable_if_t<std::is_base_of_v<Serializable, T>>> {
public:
static std::size_t write(std::ostream& os, const Serializable& value)
{
    return value.serialize(os);
}

};

} // namespace common::serialization

