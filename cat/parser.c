#include "./parser.h"

#include <string.h>

#include "../common/option.h"
#include "./helpers.h"

void gnuParse(CatOption *option, const char *arg) {
  if (!strcmp(arg, "--number-nonblank")) {
    option->b = 1;
  } else if (!strcmp(arg, "--number")) {
    option->n = 1;
  } else if (!strcmp(arg, "--squeeze-blank")) {
    option->s = 1;
  }
}

void optionParse(CatOption *option, const char *arg) {
  char *tmp = (char *)arg + 1;

  while (*tmp != '\0') {
    switch (*tmp) {
      case 'b':
        option->b = 1;
        break;
      case 'e':
        option->e = 1;
        option->v = 1;
        break;
      case 'n':
        option->n = 1;
        break;
      case 's':
        option->s = 1;
        break;
      case 't':
        option->t = 1;
        option->v = 1;
        break;
      case 'v':
        option->v = 1;
        break;
      case 'T':
        option->t = 1;
        break;
      case 'E':
        option->e = 1;
        break;
    }

    tmp++;
  }
}

void optionPriority(CatOption *option) {
  if (option->b) {
    option->n = 0;
  }
}

CatOption parseArg(int argc, char const *argv[]) {
  CatOption option = {0, 0, 0, 0, 0, 0};

  for (int i = 1; i < argc; i++) {
    const char *arg = argv[i];
    if (isGnu(arg)) {
      gnuParse(&option, arg);
    } else if (isOption(arg)) {
      optionParse(&option, arg);
    }
  }

  optionPriority(&option);

  return option;
}
