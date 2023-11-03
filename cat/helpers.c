#include "./helpers.h"

#include <string.h>

int isGnu(const char *arg) {
  const char *GNU_OPTIONS[] = {"--number-nonblank", "--number",
                               "--squeeze-blank"};
  int result = 0, length = 3;

  for (int i = 0; i < length && !result; i++) {
    if (!strcmp(GNU_OPTIONS[i], arg)) {
      result = 1;
    }
  }

  return result;
}
