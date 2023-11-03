#include "./monad.h"

#include <stdio.h>

void createMonadTesting();
void nothingMonadTesting();
void isSomeMonadTesting();
void isNothingMonadTesting();
void mapMonadTesting();
void *sum(void *value);

int main() {
  createMonadTesting();
  nothingMonadTesting();
  isSomeMonadTesting();
  isNothingMonadTesting();
  mapMonadTesting();
  return 0;
}

void *sum(void *value) {
  *((int *)value) = *((int *)value) + 5;
  return value;
}

void createMonadTesting() {
  printf("Should create monad\n");
  int variable = 4;
  Maybe monad = createMonad(&variable);
  if (*((int *)monad.value) == variable) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
}

void nothingMonadTesting() {
  printf("Should nothing monad\n");
  Maybe monad = nothingMonad();
  if (monad.value == NULL) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
}

void isSomeMonadTesting() {
  printf("Should isSome correct\n");
  int variable = 4;
  Maybe monad = createMonad(&variable);
  if (isSomeMonad(monad)) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
  monad.value = NULL;
  if (!isSomeMonad(monad)) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
}

void isNothingMonadTesting() {
  printf("Should isNothing correct\n");
  int variable = 4;
  Maybe monad = createMonad(&variable);
  if (!isNothingMonad(monad)) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
  monad.value = NULL;
  if (isNothingMonad(monad)) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
}

void mapMonadTesting() {
  printf("Should map monad testing\n");
  int variable = 4;
  Maybe monad = createMonad(&variable);
  void *(*fn)(void *) = sum;
  monad = mapMonad(monad, fn);
  if (*((int *)monad.value) == 9) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
  monad = nothingMonad();
  monad = mapMonad(monad, fn);
  if (monad.value == NULL) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
}
