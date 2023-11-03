CC=gcc
CFLAGS=-Wall -Werror -Wextra
RESULT=s21_cat
LIB=../common
FILES=main.c cat.c validator.c ../common/option.c ../common/string.c parser.c helpers.c
UNIT_TESTS=2

all: rebuild

rebuild: clean cat

cat:
	$(CC) $(CFLAGS) $(FILES) -o $(RESULT)

format:
	clang-format -i *.h
	clang-format -i *.c


check:
	clang-format -n *.h
	clang-format -n *.c
	cppcheck --enable=all --suppress=missingIncludeSystem ../**/*.c

clean:
	rm -rf s21_cat*
