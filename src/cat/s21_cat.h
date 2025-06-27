#pragma once  // S21_CAT_H

#include <getopt.h>
#include <stdio.h>

#define false 0
#define true 1

typedef enum CAT_FLAGS { B, E, N, S, T, V, cat_flag_size } cat_f;

int parse_args(int argc, char **argv, int *flags);
void main_loop(int const flags[cat_flag_size], char **argv, int argc);
int main(int argc, char **argv);
int flagV(char *c);
void flagS(const char *c, int *empty_line, int *flag_S);

static struct option long_options[] = {
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {"number-nonblank", no_argument, NULL, 'b'}};
