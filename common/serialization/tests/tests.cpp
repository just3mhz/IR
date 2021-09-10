#include "../serialize.h"

#include <gtest/gtest.h>

namespace {

class SerializableClass final: public common::serialization::Serializable
{
public:
    SerializableClass() = default;
    SerializableClass(bool b, std::string s, int i)
        : boolValue(b)
        , stringValue(std::move(s))
        , intValue(i)
    {}

    auto serialize(std::ostream& os) const -> std::size_t override {
        std::size_t bytes = 0;
        bytes += common::serialization::write(os, boolValue);
        bytes += common::serialization::write(os, stringValue);
        bytes += common::serialization::write(os, intValue);
        return bytes;
    }

    auto deserialize(std::istream& is) -> std::size_t override {
        std::size_t bytes = 0;
        bytes += common::serialization::read(is, boolValue);
        bytes += common::serialization::read(is, stringValue);
        bytes += common::serialization::read(is, intValue);
        return bytes;
    }

    auto serialized_size() const noexcept -> std::size_t override {
        const auto len = static_cast<uint32_t>(stringValue.size());
        return sizeof(boolValue) + sizeof(intValue) + (sizeof(len) + len);
    }

    bool operator==(const SerializableClass& other) const {
        return boolValue == other.boolValue && stringValue == other.stringValue && intValue == other.intValue;
    }

private:
    bool boolValue{true};
    std::string stringValue{"Initial string"};
    int intValue{-1};
};

}


TEST(TestIntegralTypes, TestInt)
{
    std::stringstream s;

    int32_t read = 0;
    int32_t write = 123456;
    common::serialization::write(s, write);
    common::serialization::read(s, read);

    ASSERT_EQ(read, write);
}

TEST(TestIntegralTypes, TestDouble)
{
    std::stringstream s;

    double read = 0;
    double write = 123456;
    common::serialization::write(s, write);
    common::serialization::read(s, read);

    ASSERT_EQ(read, write);
}

TEST(TestSpecialTypes, TestBool)
{
    std::stringstream s;

    bool read = true;
    bool write = false;

    common::serialization::write(s, write);
    common::serialization::read(s, read);
    ASSERT_EQ(read, write);

    read = false;
    write = true;
    common::serialization::write(s, write);
    common::serialization::read(s, read);
    ASSERT_EQ(read, write);
}

TEST(TestSpecialTypes, TestString)
{
    std::stringstream s;

    std::string write("Some useful string");
    std::string read;
    common::serialization::write(s, write);
    common::serialization::read(s, read);
    ASSERT_EQ(write, read);
}

TEST(TestSpecialTypes, TestSerializable)
{
    std::stringstream s;

    SerializableClass obj1(false, "Test", 128);
    SerializableClass obj2;
    std::size_t bytes1 = common::serialization::write(s, obj1);
    std::size_t bytes2 = common::serialization::read(s, obj2);

    ASSERT_EQ(bytes1, bytes2);
    ASSERT_EQ(obj1, obj2);
}