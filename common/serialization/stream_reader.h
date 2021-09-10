#pragma once

#include "serializable.h"

#include <iostream>

namespace common::serialization {

template <class T, class U = void>
class StreamReader {
public:
    static std::size_t read(std::istream& is, T& value)
    {
        const auto pos = is.tellg();
        is.read(reinterpret_cast<char*>(&value), sizeof(value));
        return static_cast<std::size_t>(is.tellg() - pos);
    }
};

template <>
class StreamReader<bool> {
public:
    static std::size_t read(std::istream& is, bool& value)
    {
        const auto pos = is.tellg();

        uint8_t tmp = 0;
        is.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));

        if (tmp == t_value) {
            value = true;
        } else if (tmp == f_value) {
            value = false;
        } else {
            // TODO: Logging or exception
            std::cerr << "Unexpected byte: "
                      << static_cast<uint32_t>(tmp)
                      << "; Expected: "
                      << static_cast<uint32_t>(t_value)
                      << "or "
                      << static_cast<uint32_t>(f_value);
        }

        return static_cast<std::size_t>(is.tellg() - pos);
    }
private:
    static constexpr auto t_value = static_cast<std::uint8_t>('T');
    static constexpr auto f_value = static_cast<std::uint8_t>('F');
};

template <>
class StreamReader<std::string> {
public:
    static std::size_t read(std::istream& is, std::string& value)
    {
        const auto pos = is.tellg();

        std::uint32_t len;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));

        std::string s;
        s.resize(len);

        if (len > 0)
            is.read(s.data(), len);

        auto bytesRead = static_cast<std::size_t>(is.tellg() - pos);
        if (bytesRead < sizeof(len) + len) {
            // TODO: Logging or exception
            std::cerr << "Byte read: " << bytesRead << "; Expected: " << sizeof(len) + len << std::endl;
        }

        value = std::move(s);

        return bytesRead;
    }
};

template <class T>
class StreamReader<T, std::enable_if_t<std::is_base_of_v<Serializable, T>>> {
public:
    static std::size_t read(std::istream& is, Serializable& value)
    {
        return value.deserialize(is);
    }
};

} // namespace common::serialization