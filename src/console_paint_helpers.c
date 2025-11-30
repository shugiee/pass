#include "number_helpers.h"
#include <asm-generic/ioctls.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define RESET "\x1b[0m"

char *repeat_char(char c, int n) {
    char *s = malloc(n + 1); // +1 for null terminator
    if (!s)
        return NULL;
    memset(s, c, n);
    s[n] = '\0';
    return s;
}

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
    printf("┐\n");

    printf("│%s│\n", repeat_char(' ', window_width - 2));
    printf("│%s│\n", repeat_char(' ', window_width - 2));
    printf("│ Password: %s %s │\n", password,
           repeat_char(' ', window_width - 15 - strlen(password)));
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
