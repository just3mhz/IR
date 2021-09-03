#include <gtest/gtest.h>

#include "test_framework/test_runner.h"
#include "document/tests/tests.h"
#include "tokenization/tests/tests.h"

void TestAll();

int main(int argc, char **argv) {
    TestAll();

    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}

void TestAll() {
    TestRunner testRunner;
    // document::tests::TestAll(testRunner);
    tokenization::tests::TestAll(testRunner);
}

