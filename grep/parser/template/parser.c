#include "./parser.h"
#include "../../../lib/string.h"
#include "../../../lib/option.h"
#include "../shared.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_BUFFER_LENGTH 1024

void pushTemplate(t_template_parser* template, char* value) {
	template->values[template->length] = value;
	template->length++;
}

t_template_parse_error parseTemplateFromFile(const char* fileName, t_template_parser* template) {
	t_template_parse_error error = {0};
	FILE *file = fopen(fileName, "r");

	if (file == NULL) {
		error.code = TEMPLATE_FILE_NOT_FOUND_ERROR;
		error.message = (char*)fileName;
		return error;
	} 
	
	char buff[FILE_BUFFER_LENGTH];
	while(fgets(buff, FILE_BUFFER_LENGTH, file)) {
		char *tmp = strCopy(buff);
		tmp[strlen(tmp) - 1] = '\0';
		pushTemplate(template, tmp);
	}

	return error;
}

t_template_parse_error parseGrepTemplate(int argc, char** argv, t_template_parser* template, int maxTemplateCount) {
	t_template_parse_error error = {0, NULL};
	template->length = 0;
	template->hasAddTemplateOption = 0;
	template->values = malloc(maxTemplateCount);

	for (int i = 1; i < argc && !error.code; i++) {
		const char* param = argv[i];
		int code = isAddTemplateOption(param);
		if (!code) continue;
		template->hasAddTemplateOption = 1;
		if (code && i >= argc - 1) {
			error.code = TEMPLATE_INVALID_ADDED_TEMPLATE;
		} else if (code == IS_OPTION_TEMPLATE) {
			pushTemplate(template, strCopy((char*)argv[++i]));
		} else if (code == IS_FILE_TEMPLATE) {
			error = parseTemplateFromFile(argv[++i], template);
		}
	}

	if (!template->hasAddTemplateOption) {
		pushTemplate(template, strCopy(argv[1]));
	}

	return error;
}

void freeGrepTemplate(t_template_parser* template) {
	for (int i = 0; i < template->length; i++) {
		free(template->values[i]);
	}
	free(template->values);
}
