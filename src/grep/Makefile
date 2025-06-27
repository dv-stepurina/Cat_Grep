FLAGS = -std=c11 -Wall -Werror -Wextra

all: build

re:  clean build

build: s21_grep


test: s21_grep
	sh test.sh

s21_grep: s21_grep.c
	gcc $(FLAGS) s21_grep.c -o s21_grep 

style:
	cppcheck --check-level=exhaustive s21_grep.c
	clang-format -n *.c *.h

clean:
	rm s21_grep res*