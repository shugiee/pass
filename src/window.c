#include "constants.h"

#include <asm-generic/ioctls.h>
#include <entropy.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

int get_window_width() {
    struct winsize window_size;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size) == -1) {
        perror("Could not determine window size\n");
        return 1;
    }
    int window_width =
        window_size.ws_col > MAX_BARS ? MAX_BARS : window_size.ws_col;

    return window_width;
};
