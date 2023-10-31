#include "./parser.h"
#include <stdio.h>
#include <string.h>

void parseGrepFileTest();

int main() {
  parseGrepFileTest();

  return 0;
}

void parseGrepFileTest() {
  printf("-- parseGrepFile testing --\n");
  printf("Should parse files\n");
  int argc = 7;
  const char *argv[] = {"./grep", "-e",     "template", "main.c",
                        "-e",     "return", "grep.c"};
  t_file_parser files;
  t_file_parser_error error = parserGrepFile(argc, argv, &files, 1);
  if (!error.code && files.length == 2 && !strcmp(files.values[0], "main.c") &&
      !strcmp(files.values[1], "grep.c")) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
  freeParseFile(&files);

  printf("Should parse file with 3 arg\n");
  int argc2 = 3;
  const char *argv2[] = {"./grep", "template", "main.c"};
  t_file_parser files2;
  t_file_parser_error error2 = parserGrepFile(argc2, argv2, &files2, 0);
  if (!error2.code && files2.length == 1 &&
      !strcmp(files2.values[0], "main.c")) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
  freeParseFile(&files2);

  printf("Should parse file, add option after files\n");
  int argc3 = 5;
  const char *argv3[] = {"./grep", "grep.c", "main.c", "-e", "template"};
  t_file_parser files3;
  t_file_parser_error error3 = parserGrepFile(argc3, argv3, &files3, 1);
  if (!error3.code && files3.length == 2 &&
      !strcmp(files3.values[0], "grep.c") &&
      !strcmp(files3.values[1], "main.c")) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
  freeParseFile(&files3);

  printf("Should parse files, not template adder\n");
  int argc4 = 5;
  const char *argv4[] = {"./grep", "template", "main.c", "add.c", "he.c"};
  t_file_parser files4;
  t_file_parser_error error4 = parserGrepFile(argc4, argv4, &files4, 0);
  if (!error4.code && files4.length == 3 &&
      !strcmp(files4.values[0], "main.c") &&
      !strcmp(files4.values[1], "add.c") && !strcmp(files4.values[2], "he.c")) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
  freeParseFile(&files4);

  printf("Should error not file\n");
  int argc5 = 2;
  const char *argv5[] = {"./grep", "template"};
  t_file_parser files5;
  t_file_parser_error error5 = parserGrepFile(argc5, argv5, &files5, 0);
  if (error5.code == PARSER_NOT_FILE_ERROR) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
  freeParseFile(&files5);

  printf("Should error not file 2\n");
  int argc6 = 5;
  const char *argv6[] = {"./grep", "-e", "template", "-e", "lol"};
  t_file_parser files6;
  t_file_parser_error error6 = parserGrepFile(argc6, argv6, &files6, 1);
  if (error6.code == PARSER_NOT_FILE_ERROR) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
  freeParseFile(&files6);

  printf("Should error not file 3\n");
  int argc7 = 3;
  const char *argv7[] = {"./grep", "-e", "template"};
  t_file_parser files7;
  t_file_parser_error error7 = parserGrepFile(argc7, argv7, &files7, 1);
  if (error7.code == PARSER_NOT_FILE_ERROR) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
  freeParseFile(&files7);

  printf("Should error not file 4\n");
  int argc8 = 7;
  const char *argv8[] = {"./grep", "-n", "-i", "-e", "main.c", "-i", "-h"};
  t_file_parser files8;
  t_file_parser_error error8 = parserGrepFile(argc8, argv8, &files8, 1);
  if (error8.code == PARSER_NOT_FILE_ERROR) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
  freeParseFile(&files8);
}
