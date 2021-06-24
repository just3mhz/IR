#include "tests.h"

#include "../document.h"

namespace document::tests {

namespace {

void TestDocumentClass() {
    Document document(1, "1", "Some text");
    ASSERT_EQUAL(document.id(), 1);
    ASSERT_EQUAL(document.url(), "1");
    ASSERT_EQUAL(document.text(), "Some text");
}

} // namespace

void TestAll(const TestRunner& testRunner)
{
    RUN_TEST(testRunner, TestDocumentClass);
}

}