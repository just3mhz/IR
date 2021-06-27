#include "test_framework/test_runner.h"
#include "document/tests/tests.h"
#include "tokenization/tests/tests.h"

void TestAll();

int main(int argc, char **argv) {
    TestAll();
}

void TestAll() {
    TestRunner testRunner;
    document::tests::TestAll(testRunner);
    tokenization::tests::TestAll(testRunner);
}

