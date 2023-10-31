#include "./parser.h"
#include <stdio.h>

void parseGrepOptionTest();

int main() {
  parseGrepOptionTest();

  return 0;
}

void parseGrepOptionTest() {
  printf("-- parseGrepOption testing --\n");
  printf("Should parse option\n");
  int argc = 5;
  const char *argv[] = {"./grep", "-in", "template", "-os", "main.c"};
  t_option_parser option;
  t_option_parser_error error = parseGrepOption(argc, argv, &option);
  if (!error.code && option.i && option.n && option.o && option.s) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }

  printf("Should not added c o option with l\n");
  int argc2 = 5;
  const char *argv2[] = {"./grep", "-co", "template", "-l", "main.c"};
  t_option_parser option2;
  t_option_parser_error error2 = parseGrepOption(argc2, argv2, &option2);
  if (!error2.code && option2.l && !option2.c && !option2.o) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }

  printf("Should not added o option with c\n");
  int argc3 = 5;
  const char *argv3[] = {"./grep", "-co", "template", "-i", "main.c"};
  t_option_parser option3;
  t_option_parser_error error3 = parseGrepOption(argc3, argv3, &option3);
  if (!error3.code && option3.c && !option3.o) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }

  printf("Should error not found option\n");
  int argc4 = 5;
  const char *argv4[] = {"./grep", "-cow", "template", "-l", "main.c"};
  t_option_parser option4;
  t_option_parser_error error4 = parseGrepOption(argc4, argv4, &option4);
  if (error4.code == PARSER_OPTION_NOT_FOUND) {
    printf("SUCCESS\n");
  } else {
    printf("FAIL\n");
  }
}
