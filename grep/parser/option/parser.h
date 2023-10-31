typedef struct {
  int code;
  char *message;
} t_option_parser_error;

typedef struct {
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int o;
} t_option_parser;

#define PARSER_OPTION_NOT_FOUND 3001
#define PARSER_NOT_WORK 3002

t_option_parser_error parseGrepOption(int argc, const char **argv,
                                      t_option_parser *option);
