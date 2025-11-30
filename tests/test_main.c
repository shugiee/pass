#include "unity/unity.h"

void setUp(void) {};
void tearDown(void) {};

void test_addition(void) { TEST_ASSERT_EQUAL_INT(4, 2 + 2); };

void test_zero_behavior(void) { TEST_ASSERT_EQUAL_INT(0, 0); };

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_addition);
    RUN_TEST(test_zero_behavior);
    return UNITY_END();
};
