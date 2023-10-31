typedef struct {
  int code;
  char *message;
} t_file_parser_error;

typedef struct {
  int length;
  char **values;
} t_file_parser;

#define PARSER_NOT_FILE_ERROR 2001

t_file_parser_error parserGrepFile(int argc, const char **argv,
                                   t_file_parser *files,
                                   int hasAddTemplateOption);
void freeParseFile(t_file_parser *files);
