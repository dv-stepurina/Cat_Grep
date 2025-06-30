#include <getopt.h>
#include <locale.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

typedef enum GREP_FLAGS { E, I, V, C, L, N, H, S, F, O, grep_flag_size } grep_f;

#define MAX_SIZE 8192
#define false 0
#define true 1

int parse_args(int argc, char **argv, int *flags, char *text);
int main_loop(int const flags[grep_flag_size], char **argv, int argc,
              char *text);
int main(int argc, char **argv);
void e_func(int const *flags, char *text, int *count_func);
void f_func(char *text, int *count_func);
int proverki(const int *flags, int argc, int *regflag, char **argv, char *text,
             int *is_valid, regex_t *regex);
int f_open(int argc, char **argv, char *text, const int *flags);
void output(int const flags[grep_flag_size], char **argv, FILE *f,
            regex_t *regex, int files_quantity, const int *i);
void part_1(char *buffer, int *success, int *count_lines, regmatch_t *pmatch,
            regex_t *regex, int const flags[grep_flag_size],
            const int *line_number, size_t *nmatch);
void part_2(int const flags[grep_flag_size], int line_number,
            const char *buffer);
void flag_C(int const flags[grep_flag_size], int files_quantity,
            int line_number, int i, char **argv, int count_lines);