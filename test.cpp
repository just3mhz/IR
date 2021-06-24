#include "test_framework/test_runner.h"
#include "document/tests/tests.h"

void TestAll();

int main() {
    TestAll();
}

void SimpleTest() {
    ASSERT(true);
    ASSERT_EQUAL(1, 1);
    ASSERT_EQUAL(1, 2)
}

void TestAll() {
    TestRunner testRunner;
    document::tests::TestAll(testRunner);
}

