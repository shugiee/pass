#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_random_int(int max) { return rand() % (max + 1); };

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
    printf("Making a password of length %d\n", pass_len);

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
        max_char_set_index = sizeof(chars) - 2;
    }

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
