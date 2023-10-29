#include "./parser.h"
#include "../shared.h"
#include "../../../lib/option.h"
#include "../../../lib/string.h"

int parseParamOption(const char* param, t_option_parser* option) {
	char OPTIONS[] = "eivclnhsfo";
	int error = 0;
	char* tmp = (char*)param + 1;
	while(*tmp != '\0' && !error) {
		int cmp = strIncludeSym(OPTIONS, *tmp);
		if (!cmp) {
			error = PARSER_OPTION_NOT_FOUND;
			continue;
		}
		switch(*tmp) {
			case 'i':
				option->i = 1;
				break;
			case 'v':
				option->v = 1;
				break;
			case 'c':
				option->c = 1;
				break;
			case 'l':
				option->l = 1;
				break;
			case 'n':
				option->n = 1;
				break;
			case 'h':
				option->h = 1;
				break;
			case 's':
				option->s = 1;
				break;
			case 'o':
				option->o = 1;
				break;
		}
		tmp++;
	}
	return error;
}

void optionPriority(t_option_parser* option) {
	if (option->l) {
		option->c = 0;
		option->o = 0;
	}
	if (option->c) {
		option->o = 0;
	}
}

t_option_parser_error parseGrepOption(int argc, const char** argv, t_option_parser* option) {
	t_option_parser_error error = {0};
	t_option_parser tmpOption = {0, 0, 0, 0, 0, 0, 0, 0};

	for (int i = 1; i < argc && !error.code; i++) {
		const char* param = argv[i];

		if (!isOption(param)) continue;
		if (isAddTemplateOption(param)) i++;
		int errorCode = parseParamOption(param, &tmpOption);
		if (errorCode) {
			error.code = errorCode;
			error.message = (char*)param;
		}
	}

	optionPriority(&tmpOption);

	*option = tmpOption;
	return error;
}
