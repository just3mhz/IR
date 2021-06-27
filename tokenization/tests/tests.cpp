//
// Created by just3mhz on 27.06.2021.
//
#include "tests.h"

namespace tokenization::tests {

namespace {

void TestTokenizeDocument() {
    TokenizedDocument expected;
    expected.doc_id = 0;
    expected.url = "URL";
    expected.tokenized_title = {"Some", "useful", "title"};
    expected.tokenized_text = {"Some", "useful", "text"};

    document::Document document(0, "URL", "Some    useful\ttitle", "Some\nuseful\ntext");

    TokenizedDocument result = TokenizeDocument(document);
    ASSERT_EQUAL(result.doc_id, expected.doc_id)
    ASSERT_EQUAL(result.url, expected.url)
    ASSERT_EQUAL(result.tokenized_title, expected.tokenized_title);
    ASSERT_EQUAL(result.tokenized_text, expected.tokenized_text)
}

} // namespace

void TestAll(const TestRunner& testRunner)
{
    RUN_TEST(testRunner, TestTokenizeDocument);
}

} // namespace tokenization::tests
