#include <gtest/gtest.h>

#include "test_framework/test_runner.h"

void TestAll();

int main(int argc, char **argv) {
    TestAll();

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

void TestAll() {
    TestRunner testRunner;
}

