#include "./shared.h"
#include "../../lib/string.h"
#include "../../lib/option.h"

int isAddTemplateOption(const char* param) {
	int result = 0;

	if (isOption(param) && strIncludeSym((char*)param, 'e')) {
		result = IS_OPTION_TEMPLATE;
	} else if (isOption(param) && strIncludeSym((char*)param, 'f')) {
		result = IS_FILE_TEMPLATE;
	}

	return result;
}
