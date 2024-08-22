SHELL := /bin/bash
CFLAGS=-Wall -Wextra -Werror -std=c11 -D _POSIX_C_SOURCE=200809L -D _GNU_SOURCE_ -D _GNU_SOURCE
CHEAK=leaks -atExit --
FILE=1.txt 2.txt 3.txt

all: gcc test

gcc:
	gcc $(CFLAGS) s21_cat.c s21_cat.h -o s21_cat

clang:
	@cp ../../materials/linters/.clang-format .
	@clang-format -i *.c
	@clang-format -i *.h
	@rm ./.clang-format

clang-test:
	@cp ../../materials/linters/.clang-format .
	@clang-format -n *.c
	@clang-format -n *.h
	@rm ./.clang-format

clean:
	rm -f s21_cat
	@clear

test:
	-diff <(./s21_cat $(FILE)) <(cat $(FILE))
	-diff <(./s21_cat -b $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat -e $(FILE)) <(cat -e $(FILE))
	-diff <(./s21_cat -n $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat -t $(FILE)) <(cat -t $(FILE))
	-diff <(./s21_cat -s $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat -v $(FILE)) <(cat -v $(FILE))
	-diff <(./s21_cat -et $(FILE)) <(cat -et $(FILE))
	-diff <(./s21_cat -st $(FILE)) <(cat -st $(FILE))
	-diff <(./s21_cat -bn $(FILE)) <(cat -bn $(FILE))
	-diff <(./s21_cat -bs $(FILE)) <(cat -bs $(FILE))
	-diff <(./s21_cat -bntes $(FILE)) <(cat -bntes $(FILE))

leaks:
	$(CHEAK) ./s21_cat -s so *.txt

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./s21_cat *.txt