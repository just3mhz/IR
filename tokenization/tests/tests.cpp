//
// Created by just3mhz on 27.06.2021.
//
#include "tests.h"

namespace tokenization::tests {

namespace {

void TestTokenizeDocument() {
    TokenizedDocument expected;
    expected.docId = 0;
    expected.url = "URL";
    expected.tokenizedTitle = {"Some", "useful", "title"};
    expected.tokenizedText = {"Some", "useful", "text"};

    document::Document document(0, "URL", "Some    useful\ttitle", "Some\nuseful\ntext");

    TokenizedDocument result = tokenizeDocument(document);
    ASSERT_EQUAL(result.docId, expected.docId)
    ASSERT_EQUAL(result.url, expected.url)
    ASSERT_EQUAL(result.tokenizedTitle, expected.tokenizedTitle);
    ASSERT_EQUAL(result.tokenizedText, expected.tokenizedText)
}

} // namespace

void TestAll(const TestRunner& testRunner)
{
    RUN_TEST(testRunner, TestTokenizeDocument);
}

} // namespace tokenization::tests
