#include "unity/unity.h"

// Test functions defined in other test translation units
extern void test_is_number(void);
extern void test_repeat_char(void);
extern void test_get_entropy(void);

void setUp(void) {};
void tearDown(void) {};

void test_addition(void) { TEST_ASSERT_EQUAL_INT(4, 2 + 2); };

void test_zero_behavior(void) { TEST_ASSERT_EQUAL_INT(0, 0); };

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_addition);
    RUN_TEST(test_zero_behavior);
    RUN_TEST(test_is_number);
    RUN_TEST(test_repeat_char);
    RUN_TEST(test_get_entropy);
    return UNITY_END();
};
