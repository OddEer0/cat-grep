#include "./cat.h"

#include <stdio.h>
#include <string.h>

#include "../common/option.h"

typedef struct {
  int line;
  int column;
  char sym;
  int block;
  char prevSym;
  char prev2Sym;
} FileIteratorCallbackArgs;

typedef void (*pipeFunc)(FileIteratorCallbackArgs*);

int fileIterator(const char* filename, pipeFunc funcs[], int length) {
  FileIteratorCallbackArgs args = {.line = 1, .column = 1, .block = 0};
  FILE* file = fopen(filename, "r");

  if (file == NULL) {
    return 1;
  }

  char sym = 0;
  while (sym != EOF) {
    sym = fgetc(file);
    if (sym == EOF) continue;
    args.sym = sym;

    for (int i = 0; i < length; i++) {
      if (funcs[i] != NULL && !args.block) {
        funcs[i](&args);
      }
    }
    if (args.block) args.block = 0;
    args.prev2Sym = args.prevSym;
    args.prevSym = sym;
    if (sym == '\n') {
      args.line++;
      args.column = 0;
    };
    args.column++;
  }
  fclose(file);

  return 0;
}

void printCallback(FileIteratorCallbackArgs* arg) { putchar(arg->sym); }

void callbackB(FileIteratorCallbackArgs* arg) {
  if (arg->column == 1 && arg->sym != '\n') {
    printf("%6d\t", arg->line);
  } else if (arg->column == 1 && arg->sym == '\n') {
    arg->line--;
  }
}

void callbackE(FileIteratorCallbackArgs* arg) {
  if (arg->sym == '\n') {
    printf("$");
  }
}

void callbackN(FileIteratorCallbackArgs* arg) {
  if (arg->column == 1) {
    printf("%6d\t", arg->line);
  }
}

void callbackS(FileIteratorCallbackArgs* arg) {
  if (arg->prevSym == '\n' && arg->sym == '\n' && arg->prev2Sym == '\n') {
    arg->line--;
    arg->block = 1;
  }
}

void callbackT(FileIteratorCallbackArgs* arg) {
  if (arg->sym == '\t') {
    printf("^");
    arg->sym = 'I';
  }
}

void callbackV(FileIteratorCallbackArgs* arg) {
  int tmp = arg->sym;
  if ((tmp >= 32 && tmp < 127) || tmp == '\n' || tmp == '\t') {
    putchar(tmp);
  } else if (tmp < 32 || tmp == 127) {
    printf("^%c", tmp ^ 64);
  } else {
    printf("M-%c", tmp ^ 128);
  }
}

void cat(const char* files[], int fileLength, CatOption option) {
  int funcsLength = 6;
  pipeFunc funcs[] = {
      option.s ? callbackS : NULL, option.b ? callbackB : NULL,
      option.n ? callbackN : NULL, option.e ? callbackE : NULL,
      option.t ? callbackT : NULL, option.v ? callbackV : printCallback};

  for (int i = 1; i < fileLength; i++) {
    const char* file = files[i];
    if (!isOption(file)) {
      fileIterator(file, funcs, funcsLength);
    }
  }
}
