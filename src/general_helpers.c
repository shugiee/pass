#include <stdbool.h>
#include <sys/ioctl.h>
#include <unistd.h>

int get_max_char_set_index(int *max_char_set_index, int chars_length,
                           bool should_use_symbols) {
    if (should_use_symbols) {
        *max_char_set_index = chars_length - 1;
    } else {
        *max_char_set_index = chars_length - 2;
    }
    return 0;
};
