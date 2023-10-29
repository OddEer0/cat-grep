#include "./parser.h"
#include "../shared.h"
#include "../../../lib/option.h"
#include "../../../lib/string.h"
#include <stdlib.h>

void pushFile(t_file_parser* files, char* value) {
	files->values[files->length] = value;
	files->length++;
}

t_file_parser_error parserGrepFile(int argc, const char** argv, t_file_parser* files, int hasAddTemplateOption) {
	t_file_parser_error error = {0};
	files->length = 0;
	files->values = malloc(argc - 2 - hasAddTemplateOption);
	
	for (int i = 1 + !hasAddTemplateOption; i < argc; i++) {
		const char* param = argv[i];
		if (isAddTemplateOption(param)) i++;
		if (isOption(param)) continue;
		pushFile(files, strCopy((char*)param));
	}

	if (!files->length) 
		error.code = PARSER_NOT_FILE_ERROR;

	return error;
}

void freeParseFile(t_file_parser* files) {
	for (int i = 0; i < files->length; i++) {
		free(files->values[i]);
	}
	free(files->values);
}
