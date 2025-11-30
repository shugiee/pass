#include "number_helpers.h"
#include <asm-generic/ioctls.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define DEFAULT_LENGTH 25

int get_password_length(char input[100], int *pass_len) {
    // fgets allows us to detect empty inputs
    if (fgets(input, sizeof(&input), stdin) != NULL) {
        // Remove trailing newline
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0) {
            // user just pressed enter
            *pass_len = DEFAULT_LENGTH;
        } else if (is_number(input)) {
            *pass_len = atoi(input);
        } else {
            printf("Invalid input. Using default value of %d\n",
                   DEFAULT_LENGTH);
            *pass_len = DEFAULT_LENGTH;
        }
    } else {
        perror("Couldn't get password length");
        return 1;
    }
    return 0;
};

int get_should_use_symbols(char input[100], bool *should_use_symbols) {
    if (fgets(input, sizeof(&input), stdin) != NULL) {
        // Remove trailing newline
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0) {
            *should_use_symbols = true;
        } else if (tolower(input[0]) == 'n') {
            *should_use_symbols = false;
        } else {
            printf("Invalid input. Using default value of 'yes'\n");
        }
    } else {
        perror("Couldn't get indication of whether to use symbols");
        return 1;
    }
    return 0;
};
