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
        document/document_reader.cpp
        document/document_reader.h
        tokenization/tokenization.cpp
        tokenization/tokenization.h
        tokenization/filter.cpp
        tokenization/filter.h
        auxiliary/dictionary.cpp
        auxiliary/dictionary.h
        bsbi/bsbi.h
        bsbi/record.h
        bsbi/record.cpp
        bsbi/bsbi.cpp
        bsbi/block_processor.cpp
        bsbi/block_processor.h
        bsbi/record_merger.cpp
        bsbi/record_merger.h
        bsbi/postings/posting.cpp
        bsbi/postings/posting.h
        bsbi/postings/posting_list.cpp
        bsbi/postings/posting_list.h
        bsbi/postings/posting_list_builder.cpp
        bsbi/postings/posting_list_builder.h
        boolean_queries/boolean_query.cpp
        boolean_queries/boolean_query.h
        common/serialization/serialize.h
        common/serialization/serializable.h
        common/serialization/stream_writer.h
        common/serialization/stream_reader.h boolean_queries/boolean_query.h boolean_queries/boolean_query.cpp boolean_queries/token.cpp boolean_queries/token.h boolean_queries/parser.h boolean_queries/parser.cpp)

add_executable(IR_tests
        test.cpp
        document/document.cpp
        document/document.h
        document/document_reader.cpp
        document/document_reader.h
        tokenization/tokenization.cpp
        tokenization/tokenization.h
        tokenization/filter.cpp
        tokenization/filter.h
        auxiliary/dictionary.cpp
        auxiliary/dictionary.h
        auxiliary/tests/test_dictionary.cpp
        bsbi/bsbi.h
        bsbi/bsbi.cpp
        bsbi/tests/test_bsbi.cpp
        bsbi/record.h
        bsbi/record.cpp
        bsbi/block_processor.cpp
        bsbi/block_processor.h
        bsbi/record_merger.cpp
        bsbi/record_merger.h
        bsbi/postings/posting.cpp
        bsbi/postings/posting.h
        bsbi/postings/posting_list.cpp
        bsbi/postings/posting_list.h
        bsbi/postings/posting_list_builder.cpp
        bsbi/postings/posting_list_builder.h
        boolean_queries/boolean_query.cpp
        boolean_queries/boolean_query.h
        common/serialization/serialize.h
        common/serialization/serializable.h
        common/serialization/stream_writer.h
        common/serialization/stream_reader.h
        common/serialization/tests/tests.cpp boolean_queries/boolean_query.h boolean_queries/token.cpp boolean_queries/token.h boolean_queries/parser.h boolean_queries/parser.cpp)


target_link_libraries(IR_tests gtest gtest_main)
add_test(NAME IR_tests COMMAND IR_tests)