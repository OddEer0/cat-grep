#include "./parser.h"
#include <string.h>
#include <stdio.h>

void parseGrepTemplateTest();

int main() {
	parseGrepTemplateTest();

	return 0;
}

void parseGrepTemplateTest() {
	printf("-- parseGrepTemplate testing --\n");
	printf("Should parse option template\n");
	int argc = 6;
	char* argv[] = {"./grep", "-e", "template-added", "filename", "-e", "template-added-2"};
	t_template_parser template;
	t_template_parse_error error = parseGrepTemplate(argc, argv, &template, 30);
	if (!error.code 
		&& !strcmp(template.values[0], "template-added") 
		&& !strcmp(template.values[1], "template-added-2") 
		&& template.length == 2
	) {
		printf("SUCCESS\n");
	} else {
		printf("FAIL\n");
	}
	freeGrepTemplate(&template);

	printf("Should parse file template\n");
	int argc2 = 6;
	char* argv2[] = {"./grep", "-f", "template.txt", "filename", "-f", "template2.txt"};
	t_template_parser template2;
	t_template_parse_error error2 = parseGrepTemplate(argc2, argv2, &template2, 30);
	if (!error2.code 
		&& !strcmp(template2.values[0], "return") 
		&& !strcmp(template2.values[1], "all") 
		&& !strcmp(template2.values[2], "lol") 
		&& !strcmp(template2.values[3], "league") 
		&& template2.length == 4
	) {
		printf("SUCCESS\n");
	} else {
		printf("FAIL\n");
	}
	freeGrepTemplate(&template2);

	printf("Should error not found file\n");
	int argc3 = 6;
	char* argv3[] = {"./grep", "-f", "template.txt", "filename", "-f", "template3.txt"};
	t_template_parser template3;
	t_template_parse_error error3 = parseGrepTemplate(argc3, argv3, &template3, 30);
	if (error3.code == TEMPLATE_FILE_NOT_FOUND_ERROR && !strcmp(error3.message, "template3.txt")) {
		printf("SUCCESS\n");
	} else {
		printf("FAIL\n");
	}
	freeGrepTemplate(&template3);

	printf("Should error invalid added option\n");
	int argc4 = 5;
	char* argv4[] = {"./grep", "-f", "template.txt", "filename", "-f"};
	t_template_parser template4;
	t_template_parse_error error4 = parseGrepTemplate(argc4, argv4, &template4, 30);
	if (error4.code == TEMPLATE_INVALID_ADDED_TEMPLATE) {
		printf("SUCCESS\n");
	} else {
		printf("FAIL\n");
	}
	freeGrepTemplate(&template4);

	printf("Should add template 2 option, not add template flag\n");
	int argc5 = 3;
	char* argv5[] = {"./grep", "return", "main.c"};
	t_template_parser template5;
	t_template_parse_error error5 = parseGrepTemplate(argc5, argv5, &template5, 30);
	if (!error5.code && template5.length == 1 && !strcmp(template5.values[0], "return")) {
		printf("SUCCESS\n");
	} else {
		printf("FAIL\n");
	}
	freeGrepTemplate(&template5);

	printf("Should add template, skip 2 3 param\n");
	int argc6 = 5;
	char* argv6[] = {"./grep", "isFile", "main.c", "-e", "return"};
	t_template_parser template6;
	t_template_parse_error error6 = parseGrepTemplate(argc6, argv6, &template6, 30);
	if (!error6.code && template6.length == 1 && !strcmp(template6.values[0], "return")) {
		printf("SUCCESS\n");
	} else {
		printf("FAIL\n");
	}
	freeGrepTemplate(&template6);
}
