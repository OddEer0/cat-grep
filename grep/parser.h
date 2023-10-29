#include "./parser/template/parser.h"
#include "./parser/option/parser.h"
#include "./parser/file/parser.h"

#define MAX_TEMPLATE_COUNT 50

typedef struct {
	t_file_parser* files;
	t_option_parser* option;
	t_template_parser* templates;
} t_grep_parse;

typedef struct {
	int code;
	char* message;
} t_grep_error;

void grepParserErrorHandler(int code, char* message);
t_grep_error grepParser(int argc, const char** argv, t_grep_parse* grepParser);
void freeGrepParse(t_grep_parse* grepParser);
