#include <stdio.h>
#include "./shared.h"

void isAddTemplateOptionTest();

int main() {
	isAddTemplateOptionTest();

	return 0;
}

void isAddTemplateOptionTest() {
	printf("-- isAddTemplateOption testing --\n");
	printf("Should is files add template param\n");
	const char param[] = "-f";
	if (isAddTemplateOption(param) == IS_FILE_TEMPLATE) {
		printf("SUCCESS\n");
	} else {
		printf("FAIL\n");
	}

	printf("Should is option add template param\n");
	const char param2[] = "-e";
	if (isAddTemplateOption(param2) == IS_OPTION_TEMPLATE) {
		printf("SUCCESS\n");
	} else {
		printf("FAIL\n");
	}

	printf("Should return 0 not add param\n");
	const char param3[] = "-i";
	if (!isAddTemplateOption(param3)) {
		printf("SUCCESS\n");
	} else {
		printf("FAIL\n");
	}
}
