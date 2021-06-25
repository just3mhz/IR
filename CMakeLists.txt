cmake_minimum_required(VERSION 3.19)
project(IR)

set(CMAKE_CXX_STANDARD 20)

add_executable(IR main.cpp test_framework/test_runner.h document/document.cpp document/document.h document/tests/tests.h document/tests/tests.cpp document/document_reader.cpp document/document_reader.h document/document_reader_iterator.cpp document/document_reader_iterator.h)
add_executable(IR_tests test.cpp document/document.cpp document/document.h document/tests/tests.h document/tests/tests.cpp document/document_reader.cpp document/document_reader.h document/document_reader_iterator.cpp document/document_reader_iterator.h)