#include <asm-generic/ioctls.h>
#include <math.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <unistd.h>

int get_entropy(const char *chars[], int max_char_set_index,
                int password_length) {
    int char_set_length = 0;

    for (int i = 0; i < max_char_set_index; i++) {
        int set_length = (int)(sizeof(&chars[i]) / sizeof(chars[i][0])) - 1;
        char_set_length += set_length;
    }

    int log_len = log2(char_set_length);

    return password_length * log_len;
};
