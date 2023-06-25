#pragma once
#include <limits.h>
#include <stdbool.h>

enum Token {
  LA_START = CHAR_MAX,
  LA_STOP,
  END,
};

const char *token_name(enum Token token);

void use_on_la_start(char c);

void use_on_la_stop(char c);

bool S_regmatch_draft(const char *string, const enum Token *pattern,
                      int *pos, int *len);
