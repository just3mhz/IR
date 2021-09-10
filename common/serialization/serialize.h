#pragma once

#include <iostream>

namespace common::serialization {

namespace {
constexpr auto t_value = static_cast<std::uint8_t>('T');
constexpr auto f_value = static_cast<std::uint8_t>('F');
}

class Serializable {
public:
    virtual ~Serializable() = default;

    virtual auto serialize(std::ostream& os) const -> std::size_t = 0;
    virtual auto deserialize(std::istream& is) -> std::size_t = 0;
    virtual auto serialized_size() const noexcept -> std::size_t = 0;
};

template <class T, class U = void>
class StreamWriter {
public:
    static auto write(std::ostream& os, const T& value) -> std::size_t
    {
        const auto pos = os.tellp();
        os.write(reinterpret_cast<const char*>(&value), sizeof(value));
        return static_cast<std::size_t>(os.tellp() - pos);
    }
};

template <class T>
auto write(std::ostream& os, const T& value) -> std::size_t {
    return StreamWriter<T>::write(os, value);
}

template <>
class StreamWriter<bool> {
public:
    static auto write(std::ostream& os, const bool& value) -> std::size_t
    {
        const auto pos = os.tellp();
        const auto tmp = (value) ? t_value : f_value;
        os.write(reinterpret_cast<const char*>(&tmp), sizeof(tmp));
        return static_cast<std::size_t>(os.tellp() - pos);
    }
};

template <>
class StreamWriter<std::string> {
public:
    static auto write(std::ostream& os, const std::string& value) -> std::size_t
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
    static auto write(std::ostream& os, const Serializable& value) -> std::size_t
    {
        return value.serialize(os);
    }
};

template <class T, class U = void>
class StreamReader {
public:
    static auto read(std::istream& is, T& value) -> std::size_t
    {
        const auto pos = is.tellg();
        is.read(reinterpret_cast<char*>(&value), sizeof(value));
        return static_cast<std::size_t>(is.tellg() - pos);
    }
};

template <class T>
auto read(std::istream& is, T& value) -> std::size_t
{
    return StreamReader<T>::read(is, value);
}

template <>
class StreamReader<bool> {
public:
    static auto read(std::istream& is, bool& value) -> std::size_t
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
};

template <>
class StreamReader<std::string> {
public:
    static auto read(std::istream& is, std::string& value) -> std::size_t
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
    static auto read(std::istream& is, Serializable& value) -> std::size_t
    {
        return value.deserialize(is);
    }
};


} // namespace common::serialization


