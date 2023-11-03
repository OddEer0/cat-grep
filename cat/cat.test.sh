#!/bin/bash

TEST_TMP1="tmp1"
TEST_TMP2="tmp2"
Red='\033[0;31m'
Green='\033[0;32m'
Purple='\033[0;35m'
NC='\033[0m'

make all

SUCCESS_COUNT=0
FAIL_COUNT=0

function fn {
	cat $1 $2 > $TEST_TMP1
	./s21_cat $1 $2 > $TEST_TMP2
	if cmp $TEST_TMP1 $TEST_TMP2 -s;
	then
		echo "${Purple}Command: ./s21_cat $1 $2${NC}"
		echo "${Green}SUCCESS${NC}";
		SUCCESS_COUNT=$((SUCCESS_COUNT + 1))
	else
		echo "${Purple}Command: ./s21_cat $1 $2${NC}"
		echo "${Red}FAIL${NC}";
		FAIL_COUNT=$((FAIL_COUNT + 1))
	fi
	rm $TEST_TMP1
	rm $TEST_TMP2
}

# option testing array
options=("-b" "-e" "-n" "-s" "-t" "-v" "-be" "-st" "-bs")
files=("Makefile" "__test__/test_1_cat.txt" "__test__/test_2_cat.txt" "__test__/test_3_cat.txt" "__test__/test_4_cat.txt" "__test__/test_case_cat.txt")

for ix in ${!options[@]}
do
	for x in ${!files[@]}
	do
  		fn ${options[$ix]} ${files[$x]}
	done
done

make clean

echo "${Green}Success: $SUCCESS_COUNT${NC}"
echo "${Red}Fail: $FAIL_COUNT${NC}"