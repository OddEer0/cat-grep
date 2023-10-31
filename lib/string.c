#include "./string.h"
#include <stdlib.h>
#include <string.h>

int strIncludeSym(char *str, char sym) {
  int result = 0;
  char *ptr = str;

  while (*ptr != '\0' && !result) {
    if (*ptr == sym) {
      result = 1;
    }
    ptr++;
  }

  return result;
}

char *strCopy(char *str) {
  size_t length = strlen(str);
  char *result = malloc(length + 1);
  strcpy(result, str);
  result[length] = '\0';
  return result;
}

char *strPlus(char *firstStr, char *secondStr) {
  size_t firstLength = strlen(firstStr), secondLength = strlen(secondStr),
         resultLength = firstLength + secondLength;
  char *result = malloc(resultLength + 1);

  for (int i = 0; i < (int)firstLength; i++) {
    result[i] = firstStr[i];
  }
  result[firstLength] = '\0';

  strcat(result, secondStr);
  return result;
}
