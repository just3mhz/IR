cmake_minimum_required(VERSION 3.17)
project(IR)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(IR
        main.cpp
        test_framework/test_runner.h
        document/document.cpp
        document/document.h
        document/tests/tests.h
        document/tests/tests.cpp
        document/document_reader.cpp
        document/document_reader.h
        document/document_reader_iterator.cpp
        document/document_reader_iterator.h
        tokenization/tokenization.cpp
        tokenization/tokenization.h
        tokenization/tests/tests.h
        tokenization/tests/tests.cpp
        auxiliary/dictionary.cpp
        auxiliary/dictionary.h
        auxiliary/tests/test_dictionary.cpp
        bsbi/bsbi.h)

add_executable(IR_tests
        test.cpp
        document/document.cpp
        document/document.h
        document/tests/tests.h
        document/tests/tests.cpp
        document/document_reader.cpp
        document/document_reader.h
        document/document_reader_iterator.cpp
        document/document_reader_iterator.h
        tokenization/tokenization.cpp
        tokenization/tokenization.h
        tokenization/tests/tests.h
        tokenization/tests/tests.cpp
        auxiliary/dictionary.cpp
        auxiliary/dictionary.h
        auxiliary/tests/test_dictionary.cpp)

target_link_libraries(IR_tests gtest gtest_main)
add_test(NAME IR_tests COMMAND IR_tests)