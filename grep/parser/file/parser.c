#include "./parser.h"
#include "../shared.h"
#include "../../../lib/option.h"
#include "../../../lib/string.h"
#include <stdlib.h>
#include <stdio.h>

void pushFile(t_file_parser* files, char* value) {
	files->values[files->length] = value;
	files->length++;
}

t_file_parser_error parserGrepFile(int argc, const char** argv, t_file_parser* files, int hasAddTemplateOption) {
	t_file_parser_error error = {0};
	files->length = 0;
	files->values = malloc(argc * sizeof(char*));
	int hasTemplate = hasAddTemplateOption;
	
	for (int i = 1; i < argc; i++) {
		const char* param = argv[i];
		if (isAddTemplateOption(param)) i++;
		if (isOption(param)) continue;
		if (!hasTemplate) {
			hasTemplate = 1;
		} else {
			pushFile(files, strCopy((char*)param));
		}
	}

	if (!files->length) 
		error.code = PARSER_NOT_FILE_ERROR;

	return error;
}

void freeParseFile(t_file_parser* files) {
	for (int i = 0; i < files->length; i++) {
		if (files->values[i] != NULL) {
			free(files->values[i]);
		}
	}
	if (files != NULL) {
		free(files->values);
	}
}
