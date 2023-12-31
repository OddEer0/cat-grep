#include "./parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../common/option.h"
#include "../../../common/string.h"
#include "../shared.h"

#define FILE_BUFFER_LENGTH 1024

void pushTemplate(t_template_parser *template, char *value) {
  template->values[template->length] = value;
  template->length++;
}

void removeNextLineSymbol(char *str) {
  size_t length = strlen(str);
  if (str[length - 1] == '\n') {
    str[length - 1] = '\0';
  }
}

t_template_parse_error parseTemplateFromFile(const char *fileName,
                                             t_template_parser *template) {
  t_template_parse_error error = {0};
  FILE *file = fopen(fileName, "r");

  if (file == NULL) {
    error.code = TEMPLATE_FILE_NOT_FOUND_ERROR;
    error.message = (char *)fileName;
    return error;
  }

  char buff[FILE_BUFFER_LENGTH];
  while (fgets(buff, FILE_BUFFER_LENGTH, file)) {
    char *tmp = strCopy(buff);
    removeNextLineSymbol(tmp);
    pushTemplate(template, tmp);
  }

  return error;
}

t_template_parse_error parseGrepTemplate(int argc, const char **argv,
                                         t_template_parser *template,
                                         int maxTemplateCount) {
  t_template_parse_error error = {0, NULL};
  template->length = 0;
  template->hasAddTemplateOption = 0;
  template->values = malloc(maxTemplateCount * sizeof(char *));
  int reallocCount = 0;

  for (int i = 1; i < argc && !error.code; i++) {
    if (i >= maxTemplateCount * (reallocCount + 1)) {
      reallocCount++;
      template->values =
          realloc(template->values, maxTemplateCount * (reallocCount + 1));
    }
    const char *param = argv[i];
    int code = isAddTemplateOption(param);
    if (!code) continue;
    template->hasAddTemplateOption = 1;
    if (code && i >= argc - 1) {
      error.code = TEMPLATE_INVALID_ADDED_TEMPLATE;
    } else if (code == IS_OPTION_TEMPLATE) {
      pushTemplate(template, strCopy((char *)argv[++i]));
    } else if (code == IS_FILE_TEMPLATE) {
      error = parseTemplateFromFile(argv[++i], template);
    }
  }

  if (!template->hasAddTemplateOption) {
    int isHas = 0;
    for (int i = 1; i < argc && !isHas; i++) {
      const char *param = argv[i];
      if (!isOption(param)) {
        isHas = 1;
        pushTemplate(template, strCopy((char *)param));
      }
    }
  }

  template->values =
      realloc(template->values, template->length * sizeof(char *));

  return error;
}

void freeGrepTemplate(t_template_parser *template) {
  for (int i = 0; i < template->length; i++) {
    if (template->values[i] != NULL) free(template->values[i]);
  }
  if (template->values != NULL) free(template->values);
}
