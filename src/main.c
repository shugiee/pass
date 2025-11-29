#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET "\x1b[0m"
#define DEFAULT_LENGTH 25

const int BARS = 100;
const int MAX_ENTROPY = 128;

int get_random_int(int max) { return rand() % (max + 1); };

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

int is_number(const char *s) {
    if (*s == '\0')
        return 0; // empty string
    for (int i = 0; s[i]; i++) {
        if (!isdigit((unsigned char)s[i]))
            return 0;
    }
    return 1;
};

void print_color_block(int idx) {
    double gamma = 1.4;
    double t = pow(1 - (float)idx / BARS, gamma); // smooth curve
    int r = (int)(255 * t);
    int g = (int)(200 * (1 - t));
    int b = (int)(60 * (1 - t) + 30 * t);
    printf("\x1b[38;2;%d;%d;%dm█\x1b[0m", r, g, b);
}

void print_bar(double ratio) {
    int width = BARS; // Number of blocks in the bar
    int filled = (int)(ratio * width);

    printf("[");
    for (int i = 0; i < width; i++) {
        if (i < filled) {
            print_color_block(i);
        } else {
            printf(" ");
        }
    }
    printf("%s", RESET);
    printf("]\n");
};

int main() {
    int pass_len;
    char input[100];
    bool should_include_symbols = true;

    const char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char lower[] = "abcdefghijklmnopqrstuvwxyz";
    const char digits[] = "0123456789";
    const char symbols[] = "!@#$%^&*()_+-=[]{};':\",.<>/?\\|";
    const char *chars[] = {upper, lower, digits, symbols};

    printf("How many characters do you want your password to be? [25 chars]\n");

    // fgets allows us to detect empty inputs
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove trailing newline
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0) {
            // user just pressed enter
            pass_len = DEFAULT_LENGTH;
        } else if (is_number(input)) {
            pass_len = atoi(input);
        } else {
            printf("Invalid input. Using default value of %d\n",
                   DEFAULT_LENGTH);
            pass_len = DEFAULT_LENGTH;
        }
    }

    char password[pass_len + 1];

    printf("Do you want to include symbols? [Y/N; default Y]\n");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove trailing newline
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0) {
            should_include_symbols = true;
        } else if (tolower(input[0]) == 'n') {
            should_include_symbols = false;
        } else {
            printf("Invalid input. Using default value of 'yes'\n");
        }
    }

    int max_char_set_index;
    if (should_include_symbols) {
        max_char_set_index = (int)(sizeof(chars) / sizeof(chars[0])) - 1;
    } else {
        max_char_set_index = (int)(sizeof(chars) / sizeof(chars[0])) - 2;
    }

    int entropy = get_entropy(chars, max_char_set_index, pass_len);
    float ratio = (float)entropy / (float)MAX_ENTROPY;
    print_bar(ratio);

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
