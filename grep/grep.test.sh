#!/bin/bash

TEST_FILE="Makefile"
TEST_TMP1="tmp1"
TEST_TMP2="tmp2"

options=("-i" "-v" "-c" "-l" "-n" "-h" "-s" "-o" "-vo" "-hvi" "-cl" "-iv" "-in")

for ix in ${!options[*]}
do
  grep -e test_1_grep.txt ${commands[$ix]} $TEST_FILE > $TEST_TMP1
	./grep -e test_1_grep.txt ${commands[$ix]} $TEST_FILE > $TEST_TMP2
	RESULT=$(cmp $TEST_TMP1 $TEST_TMP2 -s)
	if $RESULT;
	then
		echo "SUCCESS";
	else
		echo "FAIL";
	fi
	rm $TEST_TMP1
	rm $TEST_TMP2
done
