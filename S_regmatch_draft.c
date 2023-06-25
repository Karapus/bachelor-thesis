#include "S_regmatch_draft.h"
#include <stdio.h>

#ifdef DEBUG
#define LOG_DEBUG(fmt, Args...) printf(fmt "\n", Args);
#else
#define LOG_DEBUG(Args...) ;
#endif

bool S_regmatch_draft(const char *string, const enum Token *pattern,
                      int *pos, int *len) {
  bool matches = false;
  int la_start, la_depth = 0, match_length = 0, i = 0, j = 0;
  do {
    LOG_DEBUG("string[%d] == %c", i, string[i]);
  reenter_switch:
    LOG_DEBUG("matching token %s", token_name(pattern[j]));
    bool current_matches;
    switch (pattern[j]) {
    case END:
      if (matches) {
        LOG_DEBUG("match of length %d detected at [%d, %d)",
                  match_length, *pos, i);
        *len = match_length;
      }
      return matches;
    case LA_START:
      ++j;
      if (la_depth++ == 0) {
        use_on_la_start(string[i]);
        la_start = i;
      }
      goto reenter_switch;
    case LA_STOP:
      ++j;
      if (--la_depth == 0) {
        use_on_la_stop(string[i]);
        match_length -= i - la_start;
      }
      goto reenter_switch;
    default:
      current_matches = pattern[j] == string[i];
      if (!matches && current_matches) {
        LOG_DEBUG("match started at %d", i);
        *pos = i;
      } else if (matches && !current_matches) {
        LOG_DEBUG("mismatch at %d", i);
        match_length = 0;
        la_depth = 0;
        j = 0;
      }
      matches = current_matches;
      if (matches) {
        ++j;
        ++match_length;
      }
    }
  } while (string[i++]);
  return false;
}
