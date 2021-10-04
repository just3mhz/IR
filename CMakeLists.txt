cmake_minimum_required(VERSION 3.17)
project(IR)

set(CMAKE_CXX_STANDARD 20)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.76.0 COMPONENTS program_options log)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(IR_LIBRARY STATIC
        document/document.cpp
        document/document.h
        document/document_reader.cpp
        document/document_reader.h
        tokenization/tokenization.cpp
        tokenization/tokenization.h
        tokenization/filter.cpp
        tokenization/filter.h
        bsbi/bsbi.h
        bsbi/record.h
        bsbi/record.cpp
        bsbi/bsbi.cpp
        bsbi/block_processor.cpp
        bsbi/block_processor.h
        bsbi/record_merger.cpp
        bsbi/record_merger.h
        bsbi/inv_index_provider.cpp
        bsbi/inv_index_provider.h
        bsbi/postings/posting.cpp
        bsbi/postings/posting.h
        bsbi/postings/posting_list.cpp
        bsbi/postings/posting_list.h
        bsbi/postings/posting_list_builder.cpp
        bsbi/postings/posting_list_builder.h
        boolean_queries/set_operations.cpp
        boolean_queries/set_operations.h
        common/serialization/serialize.h
        common/serialization/serializable.h
        common/serialization/stream_writer.h
        common/serialization/stream_reader.h
        common/handler.cpp
        common/handler.h
        common/dictionary.cpp
        common/dictionary.h
        boolean_queries/set_operations.h
        boolean_queries/set_operations.cpp
        boolean_queries/token.cpp
        boolean_queries/token.h
        boolean_queries/parser.h
        boolean_queries/parser.cpp
        boolean_queries/tokenization.cpp
        boolean_queries/tokenization.h
        boolean_queries/expression_tree.cpp
        boolean_queries/expression_tree.h
        common/utils.cpp
        common/utils.h
        search_engine/search_engine.cpp
        search_engine/search_engine.h)

add_executable(IndexBuilder
        index_builder_app.cpp logging.cpp logging.h common/dictionary.cpp common/dictionary.h)

add_executable(SearchApp search_app.cpp)

target_link_libraries(IndexBuilder IR_LIBRARY)
target_link_libraries(SearchApp IR_LIBRARY)

add_executable(IR_tests
        test.cpp
        bsbi/tests/test_bsbi.cpp
        common/serialization/tests/tests.cpp
        boolean_queries/tests/tests.cpp
        search_engine/tests/test.cpp)

target_link_libraries(IR_tests gtest gtest_main)
target_link_libraries(IR_tests IR_LIBRARY)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(IndexBuilder ${Boost_LIBRARIES} boost_log_setup)
    target_link_libraries(SearchApp ${Boost_LIBRARIES} boost_log_setup)
    target_link_libraries(IR_LIBRARY ${Boost_LIBRARIES} boost_log_setup)
endif()

add_test(NAME IR_tests COMMAND IR_tests)
