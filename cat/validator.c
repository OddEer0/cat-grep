#include "./validator.h"

#include <stdio.h>
#include <string.h>

#include "../common/option.h"
#include "../common/string.h"
#include "./helpers.h"

int optionValidate(const char *arg) {
  int isError = 0;
  char *tmp = (char *)arg + 1;
  char OPTIONS[] = "benstv";

  while (*tmp != '\0' && !isError) {
    int isNot = strIncludeSym(OPTIONS, *tmp);

    if (!isNot) {
      isError = 1;
    }

    tmp++;
  }

  return isError;
}

int catValidate(int argc, char const *argv[]) {
  int isError = 0;

  if (argc <= 1) {
    isError = 1;
  }

  for (int i = 1; i < argc - 1 && !isError; i++) {
    const char *arg = argv[i];
    if (isOption(arg)) {
      isError = !isGnu(arg);
      if (isError) isError = optionValidate(arg);
    }
  }

  return isError;
}

void errorHandler(int errorNumber) {
  if (errorNumber == 1) {
    char optionErrorMessage[] = "cat [OPTION] [FILE PATH]";
    fprintf(stderr, "%s\n", optionErrorMessage);
  }
}
