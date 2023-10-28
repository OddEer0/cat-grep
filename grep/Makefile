CC=gcc
CFLAGS=-Wall -Werror -Wextra
RESULT=grep
LIB=../lib
FILES=
TEST_TEMPLATE_PARSER_FILES=parser/template/parser.c parser/template/parser.test.c $(LIB)/string.c $(LIB)/option.c

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
	rm -rf grep*

test_template_parser:
	rm -rf test_template_parser_test*
	$(CC) $(CFLAGS) $(TEST_TEMPLATE_PARSER_FILES) -o test_template_parser_test
	cp parser/template/template.txt template.txt
	cp parser/template/template2.txt template2.txt
	./test_template_parser_test
	rm -rf test_template_parser_test*
	rm template.txt
	rm template2.txt