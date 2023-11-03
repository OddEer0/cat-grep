#include "./string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strIncludeSymTest();
void strPlusTest();
void strCopyTest();

int main(int argc, char const *argv[]) {
  strIncludeSymTest();
  strPlusTest();
  strCopyTest();
  return 0;
}

void strIncludeSymTest() {
  printf("-- strIncludeSym testing --\n");
  printf("Should return 0, if has symbol:\n");
  int result = strIncludeSym("TestingText", 'i');
  if (result == 1) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }

  printf("Should return 1, if does not symbol:\n");
  result = strIncludeSym("TestingText", 'j');
  if (!result) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
}

void strPlusTest() {
  printf("-- strPlus testing --\n");
  printf("Should plus string:\n");
  char first[] = "first ", second[] = "second";
  char *result = strPlus(first, second);

  if (!strcmp(result, "first second")) {
    printf("SUCCESS\n");
  } else {
    printf("is: %s\n", result);
    printf("FAIL\n");
  }

  free(result);
}

void strCopyTest() {
  printf("-- strCopy testing --\n");
  printf("Should copy string:\n");
  char *result = strCopy("copy text");

  if (!strcmp(result, "copy text")) {
    printf("SUCCESS\n");
  } else {
    printf("is: %s\n", result);
    printf("FAIL\n");
  }
}
