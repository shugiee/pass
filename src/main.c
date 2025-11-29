#include <asm-generic/ioctls.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define RESET "\x1b[0m"
#define DEFAULT_LENGTH 25

const int MAX_BARS = 150;
const int MAX_ENTROPY = 128;

int get_random_int(int max) { return rand() % (max + 1); };

char *repeat_char(char c, int n) {
    char *s = malloc(n + 1); // +1 for null terminator
    if (!s)
        return NULL;
    memset(s, c, n);
    s[n] = '\0';
    return s;
}

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

void print_color_block(int idx, int window_width) {
    double gamma = 1.4;
    double t = pow(1 - (float)idx / window_width, gamma); // smooth curve
    char *progress_block = "◼";
    int r = (int)(255 * t);
    int g = (int)(200 * (1 - t));
    int b = (int)(60 * (1 - t) + 30 * t);

    printf("\x1b[38;2;%d;%d;%dm%s\x1b[0m", r, g, b, progress_block);
}

void print_output_details(double ratio, int window_width, char password[]) {
    int filled = (int)(ratio * window_width);
    char *text = "Your password";

    // Top border
    printf("┌");
    for (int i = 0; i < 4; i++) {
        printf("─");
    }
    printf(" %s ", text);
    for (int i = 19; i < window_width - 2; i++) {
        printf("─");
    }
    printf("┐");

    printf("│%s│\n", repeat_char(' ', window_width - 2));
    printf("│%s│\n", repeat_char(' ', window_width - 2));
    // TODO: Copy password to clipboard
    // TODO: Don't use hardcoded values like 62
    printf("│ Password: %s %s │", password,
           repeat_char(' ', window_width - 40));
    printf("│%s│\n", repeat_char(' ', window_width - 2));
    printf("│%s│\n", repeat_char(' ', window_width - 2));
    printf("│ Strength: ");
    for (int i = 12; i < window_width - 1; i++) {
        if (i < filled) {
            print_color_block(i, window_width);
        } else {
            printf(" ");
        }
    }
    printf("%s", RESET);
    printf("│\n");
    printf("│%s│\n", repeat_char(' ', window_width - 2));
    printf("│%s│\n", repeat_char(' ', window_width - 2));
    printf("└");
    for (int i = 0; i < window_width - 2; i++) {
        printf("─");
    }
    printf("┘\n");
};

int main() {
    int pass_len;
    char input[100];
    bool should_include_symbols = true;
    struct winsize window_size;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size) == -1) {
        perror("Could not determine window size\n");
        return 1;
    }
    int window_width =
        window_size.ws_col > MAX_BARS ? MAX_BARS : window_size.ws_col;

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

    for (int i = 0; i < pass_len; i++) {
        int next_char_set_index = get_random_int(max_char_set_index);
        const char *next_char_set = chars[next_char_set_index];
        int next_char_index = get_random_int((int)strlen(next_char_set) - 1);
        char next_char = next_char_set[next_char_index];
        password[i] = next_char;
    };

    // Null-terminate the string
    password[pass_len] = '\0';

    // Output the details
    print_output_details(ratio, window_width, password);

    return 0;
}
