#pragma once

#include "stream_writer.h"
#include "stream_reader.h"
#include "serializable.h"

#include <iostream>

namespace common::serialization {

template <class T>
std::size_t write(std::ostream& os, const T& value)
{
    return StreamWriter<T>::write(os, value);
}

template <class T>
std::size_t read(std::istream& is, T& value)
{
    return StreamReader<T>::read(is, value);
}

} // namespace common::serialization


