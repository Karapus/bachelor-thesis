#include "S_regmatch_draft.h"
#include <stdio.h>

static char default_token_name_buffer[2];

const char *token_name(enum Token token) {
    switch (token) {
        case END:
            return "END";
        case LA_START:
            return "LA_START";
        case LA_STOP:
            return "LA_STOP";
        default:
            default_token_name_buffer[0] = (char)token;
            return default_token_name_buffer;
    }
}

void use_on_la_start(char c) {
    printf("Strating lookahead on input %c\n", c);
}

void use_on_la_stop(char c) {
    printf("Lookahead ended on input %c\n", c);
}

#define N_PATTERNS 3
#define PATTERN_MAX_LEN 10
int main() {
    const enum Token patterns[N_PATTERNS][PATTERN_MAX_LEN] = {
        {'a', 'a', LA_START, 'b', LA_STOP, END},
        {'a', 'a', LA_START, 'b', LA_START, 'c', LA_STOP, LA_STOP, END},
        {'b', 'e', LA_START, 'a', LA_START, 'a', LA_STOP, LA_STOP, END},
    };
    int pos, len;
    for (int i = 0; i < N_PATTERNS; ++i) {
        if (S_regmatch_draft("caacaabeaabc", patterns[i], &pos, &len)) {
            printf("match! position: %d, length %d\n", pos, len);
        } else {
            printf("no match!\n");
        }
    }
}
