#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_random_int(int max) { return rand() % (max + 1); };

// TODO: Next, calculate entropy. Then, show it in a nice TUI
// int calculate_entropy(char *
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

int main() {
    int pass_len;
    char input;
    bool should_include_symbols = true;

    const char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char lower[] = "abcdefghijklmnopqrstuvwxyz";
    const char digits[] = "0123456789";
    const char symbols[] = "!@#$%^&*()_+-=[]{};':\",.<>/?\\|";
    const char *chars[] = {upper, lower, digits, symbols};

    printf("How long do you want your password to be?\n");
    scanf(" %d", &pass_len);

    char password[pass_len + 1];

    printf("Do you want to include symbols? [Y/N; default Y]\n");
    if (scanf(" %c", &input) == 1) {
        input = tolower((unsigned char)input);
        should_include_symbols = (input == 'y');
    }

    int max_char_set_index;
    if (should_include_symbols) {
        max_char_set_index = (int)(sizeof(chars) / sizeof(chars[0])) - 1;
    } else {
        max_char_set_index = (int)(sizeof(chars) / sizeof(chars[0])) - 2;
    }

    printf("Entropy of proposed password: %d\n",
           get_entropy(chars, max_char_set_index, pass_len));

    for (int i = 0; i < pass_len; i++) {
        int next_char_set_index = get_random_int(max_char_set_index);
        const char *next_char_set = chars[next_char_set_index];
        int next_char_index = get_random_int((int)strlen(next_char_set) - 1);
        char next_char = next_char_set[next_char_index];
        password[i] = next_char;
    };

    // Null-terminate the string
    password[pass_len] = '\0';

    printf("Your password is: %s\n", password);

    return 0;
}
