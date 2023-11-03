#include <stdio.h>

#include "./cat.h"
#include "./validator.h"

int main(int argc, char const *argv[]) {
  int isError = catValidate(argc, argv);
  if (isError) {
    errorHandler(1);
    return 0;
  }
  CatOption options = parseArg(argc, argv);
  cat(argv, argc, options);
  return 0;
}
