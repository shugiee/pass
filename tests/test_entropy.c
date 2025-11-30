#include "entropy.h"
#include "unity/unity.h"

void test_get_entropy(void) {
    const char *chars[] = {"abcdefg", "ABCDEFG"};
    int max_char_set_index = 2;
    int password_length = 10;

    TEST_ASSERT_EQUAL_INT(
        30, get_entropy(chars, max_char_set_index, password_length));
}
