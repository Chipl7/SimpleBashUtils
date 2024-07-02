SHELL := /bin/bash
CFLAGS=-Wall -Wextra -Werror -std=c11 -D _POSIX_C_SOURCE=200809L -D _GNU_SOURCE_ -D _GNU_SOURCE
CHEAK=leaks -atExit --
FILE=1.txt 2.txt 3.txt 4.txt
PATTERN=pattern.reg

all:
	gcc $(CFLAGS) s21_grep.c s21_grep.h -o s21_grep

clang:
	@cp ../../linters/.clang-format .
	@clang-format -i *.c
	@clang-format -i *.h
	@rm ./.clang-format

clean:
	rm -f s21_grep

test:
	-diff <(./s21_grep -i so $(FILE)) <(grep -i so $(FILE))
	-diff <(./s21_grep -v so $(FILE)) <(grep -v so $(FILE))
	-diff <(./s21_grep -c so $(FILE)) <(grep -c so $(FILE))
	-diff <(./s21_grep -l so $(FILE)) <(grep -l so $(FILE))
	-diff <(./s21_grep -n so $(FILE)) <(grep -n so $(FILE))
	-diff <(./s21_grep -h so $(FILE)) <(grep -h so $(FILE))
	-diff <(./s21_grep -s so $(FILE)) <(grep -s so $(FILE))
	-diff <(./s21_grep -f pattern.reg $(FILE)) <(grep -f pattern.reg $(FILE))
	-diff <(./s21_grep -e so -e So -e txt $(FILE)) <(grep -e so -e So -e txt $(FILE))
	-diff <(./s21_grep -o so $(FILE)) <(grep -o so $(FILE))
	-diff <(./s21_grep -iv so $(FILE)) <(grep -iv so $(FILE))
	-diff <(./s21_grep -in so $(FILE)) <(grep -in so $(FILE))
	-diff <(./s21_grep -ie '^so' $(FILE)) <(grep -ie '^so' $(FILE))
	-diff <(./s21_grep -ince '^so' $(FILE)) <(grep -ince '^so' $(FILE))
	-diff <(./s21_grep -lh so $(FILE)) <(grep -lh so $(FILE))

leaks:
	$(CHEAK) ./s21_grep -e so -e txt -e asdasd *.txt
	$(CHEAK) ./s21_grep -o so *.txt