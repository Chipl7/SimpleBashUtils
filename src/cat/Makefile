SHELL := /bin/bash
FLAGS=-Wall -Wextra -Werror -std=c11 -D _POSIX_C_SOURCE=200809L -D _GNU_SOURCE_ -D _GNU_SOURCE
CLEAN_FIELS=s21_cat *.log
FILE=1.txt 2.txt 3.txt

all: clean gcc test

gcc:
	gcc $(FLAGS) s21_cat.c -o s21_cat

clang_format:
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	@cp ../../linters/.clang-format .
	@clang-format -i *.c *.h
	@rm ./.clang-format

clang_check:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@cp ../../linters/.clang-format .
	@clang-format -n *.c *.h
	@rm ./.clang-format

clean:
	rm -f $(CLEAN_FIELS)
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

valgrind: gcc
	@CK_FORK=no valgrind --vgdb=no --leak-check=full \
	--show-leak-kinds=all --track-origins=yes --log-file="valgrind.log" -v --verbose -q --quiet -s ./s21_cat *.txt
	@clear
	@cat valgrind.log