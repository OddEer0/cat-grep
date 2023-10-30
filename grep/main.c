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
	
	// for (int i = 0; i < grepData.files->length; i++) {
	// 	printf("files: %s\n", grepData.files->values[i]);
	// }
	// printf("length: %d\n", grepData.files->length);
	
	freeGrepParse(&grepData);
	return 0;
}

