#include "console_paint_helpers.h"
#include "constants.h"
#include "general_helpers.h"
#include "number_helpers.h"
#include "user_input_helpers.h"
#include "window.h"

#include <asm-generic/ioctls.h>
#include <entropy.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

const int MAX_ENTROPY = 128;

int main() {
    int pass_len;
    char input[100];
    bool should_use_symbols = true;
    int window_width = get_window_width();

    const char *chars[] = {upper, lower, digits, symbols};

    printf("How many characters do you want your password to be? [25 chars]\n");
    get_password_length(input, &pass_len);

    char password[pass_len + 1];

    printf("Do you want to include symbols? [Y/N; default Y]\n");
    get_should_use_symbols(input, &should_use_symbols);

    int max_char_set_index;
    int chars_length = (int)(sizeof(chars) / sizeof(chars[0]));
    get_max_char_set_index(&max_char_set_index, chars_length,
                           should_use_symbols);

    int entropy = get_entropy(chars, max_char_set_index, pass_len);
    float ratio = (float)entropy / (float)MAX_ENTROPY;

    for (int i = 0; i < pass_len; i++) {
        int next_char_set_index = get_random_int(max_char_set_index);
        const char *next_char_set = chars[next_char_set_index];
        int next_char_index = get_random_int((int)strlen(next_char_set) - 1);
        char next_char = next_char_set[next_char_index];
        password[i] = next_char;
    };

    // Null-terminate the string
    password[pass_len] = '\0';

    print_output_details(ratio, window_width, password);

    return 0;
}
