FLAGS = -Wall -Werror -Wextra -std=c11 

all: build

re: clean build

build: s21_cat

test: s21_cat
	sh test.sh

s21_cat: s21_cat.c
	gcc $(FLAGS) -o s21_cat s21_cat.c

style:
	cppcheck --suppress=missingIncludeSystem --check-level=exhaustive s21_cat.c *.h
	clang-format  -n *.c *.h

clean:
	rm s21_cat