#include "./grep.h"
#include <stdio.h>
#include <regex.h>
#include <string.h>

#define BUFFER_SIZE 1024

void printFnHelper(const char* fileName, t_grep_parse* grepData, int line, char* buff) {
	if (!grepData->option->c && !grepData->option->l) {
		if (grepData->files->length > 1 && !grepData->option->h) printf("%s:", fileName);
		if (grepData->option->n) printf("%d:", line);
		printf("%s", buff);
		if (buff[strlen(buff) - 1] != '\n') printf("\n");
	}
}

void printO(const char* fileName, t_grep_parse* grepData, char* buff, int line, regex_t* regex) {
	char* s = buff;
	regmatch_t pmatch[1];
	for (int i = 0; !regexec(regex, s, (sizeof((pmatch)) / sizeof((pmatch)[0])), pmatch, 0); i++) {
		regoff_t off = pmatch[0].rm_so + (s - buff);
		regoff_t length = pmatch[0].rm_eo - pmatch[0].rm_so;

		if (grepData->files->length > 1 && !grepData->option->h) printf("%s:", fileName);
		if (grepData->option->n) printf("%d:", line);
		for (int j = 0; j < length; j++) {
			printf("%c", *(buff + off + j));
		}
		printf("\n");

		s += pmatch[0].rm_eo;
	}
}

void printFn(const char* fileName, t_grep_parse* grepData, int* successCount, char* buff, int line) {
	int isSuccess = 0;
	int isSuccessInvert = 1;
	for (int i = 0; i < grepData->templates->length && !isSuccess; i++) {
		regex_t regex;
		int result = regcomp(&regex, grepData->templates->values[i], grepData->option->i ? REG_ICASE : 0);

		if (result) {
			// TODO - errorHandler
			continue;
		}

		if (grepData->option->o) {
			printO(fileName, grepData, buff, line, &regex);
		} else {
			result = regexec(&regex, buff, 0, NULL, 0);
			if (!result && grepData->option->v) isSuccessInvert = 0;
			if ((!result && !grepData->option->v) || (isSuccessInvert && result && grepData->option->v && i == grepData->templates->length - 1)) {
				isSuccess = 1;
				*successCount = *successCount + 1;
				printFnHelper(fileName, grepData, line, buff);
			}
		}

		regfree(&regex);
	}
}

void printCFn(const char* fileName, int filesCount, int successCount, int isH) {
	if (filesCount > 1 && !isH) printf("%s:", fileName);
	printf("%d\n", successCount);
}

void grepFile(const char* fileName, t_grep_parse* grepData) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		if (!grepData->option->s)
			fprintf(stderr, "%s: file not found\n", fileName);;
		return;
	}

	char buff[BUFFER_SIZE] = {};
	int line = 0, successCount = 0;
	while(fgets(buff, BUFFER_SIZE, file)) {
		line++;
		if (buff[0] != '\n')
			printFn(fileName, grepData, &successCount, buff, line);
	}

	if (grepData->option->c) {
		printCFn(fileName, grepData->files->length, successCount, grepData->option->h);
	} else if (grepData->option->l && successCount) {
		printf("%s\n", fileName);
	}

	fclose(file);
}

void grep(t_grep_parse* grepData) {
	for (int i = 0; i < grepData->files->length; i++) {
		grepFile(grepData->files->values[i], grepData);
	}
}
