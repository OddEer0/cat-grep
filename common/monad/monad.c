#include "./monad.h"

#include <stdio.h>

Maybe createMonad(void *pointer) {
  Maybe maybe = {pointer};
  return maybe;
}

Maybe nothingMonad() {
  Maybe maybe = {NULL};
  return maybe;
}

int isSomeMonad(Maybe maybe) { return maybe.value != NULL; }

int isNothingMonad(Maybe maybe) { return maybe.value == NULL; }

Maybe mapMonad(Maybe maybe, void *(*mapper)(void *)) {
  Maybe result;
  if (isNothingMonad(maybe)) {
    result = nothingMonad();
  } else {
    result = createMonad(mapper(maybe.value));
  }
  return result;
}

Maybe flatMapMonad(Maybe maybe, Maybe (*mapper)(void *)) {
  Maybe result;
  if (isNothingMonad(maybe)) {
    result = nothingMonad();
  } else {
    result = mapper(maybe.value);
  }
  return result;
}
