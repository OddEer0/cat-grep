#include "../parser.h"
#include <stdio.h>

t_grep_error grepParser(int argc, const char** argv, t_grep_parse* grepParser) {
	t_grep_error error = {0};
	t_option_parser option;
	t_option_parser_error optionParseError = parseGrepOption(argc, argv, &option);
	if (optionParseError.code) {
		error.code = optionParseError.code;
		error.message = optionParseError.message;
		return error;
	}
	t_template_parser template;
	t_template_parse_error templateParseError = parseGrepTemplate(argc, argv, &template, MAX_TEMPLATE_COUNT);
	if (templateParseError.code) {
		error.code = templateParseError.code;
		error.message = templateParseError.message;
		return error;
	}
	t_file_parser files;
	t_file_parser_error fileParseError = parserGrepFile(argc, argv, &files, template.hasAddTemplateOption);
	if (fileParseError.code) {
		error.code = fileParseError.code;
		error.message = fileParseError.message;
		return error;
	}

	grepParser->files = &files;
	grepParser->option = &option;
	grepParser->templates = &template;

	return error;
}

void freeGrepParse(t_grep_parse* grepParser) {
	freeGrepTemplate(grepParser->templates);
	freeParseFile(grepParser->files);
}

void grepParserErrorHandler(int code, char* message) {
	switch(code) {
		case PARSER_OPTION_NOT_FOUND:
			fprintf(stderr, "Option %s not found\n", message);
			break;
	}
}
