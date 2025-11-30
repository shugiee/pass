#include "console_paint_helpers.h"
#include "unity/unity.h"

void test_repeat_char(void) {
    char c = 'J';
    int n = 4;
    TEST_ASSERT_EQUAL_CHAR_ARRAY("JJJJ", repeat_char(c, n), n);
}
