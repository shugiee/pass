#include "number_helpers.h"
#include "unity/unity.h"

void test_is_number(void) {
    const char *num_str = "12345";
    TEST_ASSERT_EQUAL_INT(1, is_number(num_str));

    const char *non_num_str = "12a45";
    TEST_ASSERT_EQUAL_INT(0, is_number(non_num_str));

    const char *empty_str = "";
    TEST_ASSERT_EQUAL_INT(0, is_number(empty_str));

    const char *negative_number = "-123";
    TEST_ASSERT_EQUAL_INT(0, is_number(negative_number));
}
