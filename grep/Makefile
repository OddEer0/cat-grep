CC=gcc
CFLAGS=-Wall -Werror -Wextra
RESULT=grep
LIB=../lib
FILES=main.c grep.c $(LIB)/string.c $(LIB)/option.c parser/shared.c parser/template/parser.c parser/file/parser.c parser/option/parser.c parser/index.c
TEST_TEMPLATE_PARSER_FILES=parser/template/parser.c parser/template/parser.test.c parser/shared.c $(LIB)/string.c $(LIB)/option.c
TEST_FILE_PARSER_FILES=parser/file/parser.c parser/file/parser.test.c parser/shared.c $(LIB)/string.c $(LIB)/option.c
TEST_OPTION_PARSER_FILES=parser/option/parser.c parser/option/parser.test.c parser/shared.c $(LIB)/string.c $(LIB)/option.c
TEST_SHARED_PARSER_FILES=parser/shared.c parser/shared.test.c $(LIB)/string.c $(LIB)/option.c

all: rebuild

rebuild: clean grep

ez:
	$(CC) $(FILES) -o $(RESULT)

grep:
	$(CC) $(CFLAGS) $(FILES) -o $(RESULT)

format:
	clang-format -i *.h
	clang-format -i *.c


check:
	clang-format -n *.h
	clang-format -n *.c

clean:
	rm -rf grep

test_template_parser:
	rm -rf test_template_parser_test*
	$(CC) $(CFLAGS) $(TEST_TEMPLATE_PARSER_FILES) -o test_template_parser_test
	cp parser/template/template.txt template.txt
	cp parser/template/template2.txt template2.txt
	./test_template_parser_test
	rm -rf test_template_parser_test*
	rm template.txt
	rm template2.txt

test_file_parser:
	rm -rf test_file_parser_test*
	$(CC) $(CFLAGS) $(TEST_FILE_PARSER_FILES) -o test_file_parser_test
	./test_file_parser_test
	rm -rf test_file_parser_test*

test_option_parser:
	rm -rf test_option_parser_test*
	$(CC) $(CFLAGS) $(TEST_OPTION_PARSER_FILES) -o test_option_parser_test
	./test_option_parser_test
	rm -rf test_option_parser_test*

test_shared_parser:
	rm -rf test_shared_parser_test*
	$(CC) $(CFLAGS) $(TEST_SHARED_PARSER_FILES) -o test_shared_parser_test
	./test_shared_parser_test
	rm -rf test_shared_parser_test*
