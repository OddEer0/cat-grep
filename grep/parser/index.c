#include "../parser.h"
#include <stdio.h>
#include <stdlib.h>

t_grep_error grepParser(int argc, const char **argv, t_grep_parse *grepData) {
  t_grep_error error = {0};
  t_option_parser *option = malloc(sizeof(t_option_parser));
  t_option_parser_error optionParseError = parseGrepOption(argc, argv, option);
  if (optionParseError.code) {
    error.code = optionParseError.code;
    error.message = optionParseError.message;
    free(option);
    return error;
  }
  t_template_parser *template = malloc(sizeof(t_template_parser));
  t_template_parse_error templateParseError =
      parseGrepTemplate(argc, argv, template, MAX_TEMPLATE_COUNT);
  if (templateParseError.code) {
    error.code = templateParseError.code;
    error.message = templateParseError.message;
    freeGrepTemplate(template);
    free(template);
    free(option);
    return error;
  }
  t_file_parser *files = malloc(sizeof(t_file_parser));
  t_file_parser_error fileParseError =
      parserGrepFile(argc, argv, files, template->hasAddTemplateOption);
  if (fileParseError.code) {
    error.code = fileParseError.code;
    error.message = fileParseError.message;
    freeGrepTemplate(template);
    freeParseFile(files);
    free(template);
    free(files);
    free(option);
    return error;
  }

  grepData->files = files;
  grepData->option = option;
  grepData->templates = template;

  return error;
}

void freeGrepParse(t_grep_parse *grepData) {
  freeGrepTemplate(grepData->templates);
  freeParseFile(grepData->files);
  if (grepData->files != NULL)
    free(grepData->files);
  if (grepData->templates != NULL)
    free(grepData->templates);
  if (grepData->option != NULL)
    free(grepData->option);
}

void grepParserErrorHandler(t_grep_error *error) {
  switch (error->code) {
  case PARSER_OPTION_NOT_FOUND:
    fprintf(stderr, "Option %s not found\n", error->message);
    break;
  case TEMPLATE_FILE_NOT_FOUND_ERROR:
    fprintf(stderr, "%s: file not found\n", error->message);
    break;
  case TEMPLATE_INVALID_ADDED_TEMPLATE:
    fprintf(stderr, "please write: -e or -f [file]\n");
    break;
  case PARSER_NOT_FILE_ERROR:
    fprintf(stderr, "Not grep file, please write file\n");
    break;
  }
}
