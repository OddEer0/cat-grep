#include <stdio.h>
#include "./main.h"
#include "./grep.h"

int main(int argc, const char* argv[]) {
	t_grep_parse grepData;
	t_grep_error grepError = grepParser(argc, argv, &grepData);
	if (grepError.code) {
		grepParserErrorHandler(&grepError);
		return 0;
	}

	grep(&grepData);
	
	freeGrepParse(&grepData);
	return 0;
}

