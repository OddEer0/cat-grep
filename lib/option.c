#include "./option.h"

int isOption(const char* param) {
	return param[0] == '-';
}
