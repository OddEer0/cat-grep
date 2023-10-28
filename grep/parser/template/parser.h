typedef struct {
	int code;
	char* message;
} t_template_parse_error;

typedef struct {
	int length;
	char** values;
} t_template_parser;

#define TEMPLATE_FILE_NOT_FOUND_ERROR 1001
#define TEMPLATE_INVALID_ADDED_TEMPLATE 1002

t_template_parse_error parseGrepTemplate(int argc, char** argv, t_template_parser* template, int maxTemplateCount);
void freeGrepTemplate(t_template_parser* template);
