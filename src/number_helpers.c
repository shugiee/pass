#include <asm-generic/ioctls.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int get_random_int(int max) { return rand() % (max + 1); };

int is_number(const char *s) {
    if (*s == '\0')
        return 0; // empty string
    for (int i = 0; s[i]; i++) {
        if (!isdigit((unsigned char)s[i]))
            return 0;
    }
    return 1;
};
