#include "s21_grep.h"

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  char text[MAX_SIZE] = {0};
  int flags[grep_flag_size] = {0};

  if (argc < 3) {
    fprintf(stderr, "too few arguments");
  } else {
    if (parse_args(argc, argv, flags, text)) {
      f_open(argc, argv, text, flags);
    }
  }
  return 0;
}

void e_func(int const *flags, char *text, int *count_func) {
  if (*count_func == 0) {
    strncat(text, optarg, MAX_SIZE);
  }
  while (*count_func < flags[E]) {
    strncat(text, "|", MAX_SIZE);
    if (optarg != NULL) {
      strncat(text, optarg, MAX_SIZE);
    }
    (*count_func)++;
  }
}

void f_func(char *text, int *count_func) {
  FILE *f;
  // char buffer[MAX_SIZE] = {0};
  char buffer[MAX_SIZE];
  if ((f = fopen(optarg, "r")) == NULL) {
    fprintf(stderr, "grep: %s: No such file or directory (file recomp)\n",
            optarg);
  } else {
    while (fgets(buffer, MAX_SIZE, f) != NULL) {
      if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = 0;
      }

      if (*count_func == 0) {
        strncat(text, buffer, MAX_SIZE);
      } else {
        strncat(text, "|", MAX_SIZE);
        strncat(text, buffer, MAX_SIZE);
      }
      (*count_func)++;
    }
    fclose(f);
  }
}

int parse_args(int argc, char **argv, int *flags, char *text) {
  int num = 0;
  int is_valid = true;
  int count_func = 0;

  while ((num = getopt(argc, argv, "e:f:ivclnhso")) != -1 && is_valid) {
    switch (num) {
      case 'i':
        flags[I]++;
        break;
      case 'e':
        flags[E]++;
        e_func(flags, text, &count_func);
        break;
      case 'v':
        flags[V]++;
        break;
      case 'c':
        flags[C]++;
        break;
      case 'l':
        flags[L]++;
        break;
      case 'n':
        flags[N]++;
        break;
      case 'h':
        flags[H]++;
        break;
      case 's':
        flags[S]++;
        break;
      case 'o':
        flags[O]++;
        break;
      case 'f':
        flags[F]++;
        f_func(text, &count_func);
        break;
      default:
        is_valid = false;
        break;
    }
  }
  return is_valid;
}

int proverki(const int *flags, int argc, int *regflag, char **argv, char *text,
             int *is_valid, regex_t *regex) {
  int files_quantity = argc - 2;
  if (flags[I]) {
    *regflag |= REG_ICASE;
  }
  if (!flags[E] && !flags[F]) {
    text = argv[optind];
  }

  if (flags[I] + flags[V] + flags[C] + flags[L] + flags[N] + flags[H] +
      flags[S] + flags[F] + flags[O] + flags[E]) {
    files_quantity--;
  }
  if (flags[E] > 1) {
    files_quantity = files_quantity - (flags[E] - 1) * 2;
  }
  if (regcomp(regex, text, *regflag) != 0) {
    fprintf(stderr, "Could not compile regex\n");
    *is_valid = 1;
  }
  return files_quantity;
}

int f_open(int argc, char **argv, char *text, const int *flags) {
  regex_t regex;
  int is_valid = 0;
  int regflag = REG_EXTENDED;
  int i = optind + 1;
  if (flags[E] || flags[F]) {
    i = optind;
  }
  int files_quantity =
      proverki(flags, argc, &regflag, argv, text, &is_valid, &regex);
  for (; i < argc; i++) {
    FILE *f;
    if ((f = fopen(argv[i], "r")) != NULL) {
      output(flags, argv, f, &regex, files_quantity, &i);
      fclose(f);
    } else {
      if (!flags[S])
        fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                argv[optind]);
    }
  }
  regfree(&regex);
  return is_valid;
}

void output(int const flags[grep_flag_size], char **argv, FILE *f,
            regex_t *regex, int files_quantity, const int *i) {
  char buffer[MAX_SIZE] = {0};
  size_t nmatch = 1;
  regmatch_t pmatch[1] = {0};
  int success;
  int count_lines = 0;
  int line_number = 0;
  while (fgets(buffer, MAX_SIZE, f) != NULL) {
    line_number++;
    success = regexec(regex, buffer, nmatch, pmatch, 0);
    if (flags[V]) success = success ? 0 : 1;
    if (files_quantity > 1 && !(flags[H]) && !(flags[C]) && !flags[L] &&
        success != REG_NOMATCH) {
      printf("%s:", argv[*i]);
    }

    if (flags[O] && !flags[V] && success != REG_NOMATCH) {
      part_1(buffer, &success, &count_lines, pmatch, regex, flags, &line_number,
             &nmatch);
    }
    if ((!flags[O] || flags[V]) && success != REG_NOMATCH) {
      part_2(flags, line_number, buffer);
      count_lines++;
    }
  }

  if (flags[L] && count_lines) {
    printf("%s\n", argv[*i]);
  }

  flag_C(flags, files_quantity, line_number, *i, argv, count_lines);
}

void part_1(char *buffer, int *success, int *count_lines, regmatch_t *pmatch,
            regex_t *regex, int const flags[grep_flag_size],
            const int *line_number, size_t *nmatch) {
  char *cursor = buffer;
  while (!(*success)) {
    if (pmatch[0].rm_eo == pmatch[0].rm_so) {
      break;
    }
    (*count_lines)++;
    if (!flags[C] && !flags[L]) {
      if (flags[N]) {
        printf("%d:", *line_number);
      }
      printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
             cursor + pmatch[0].rm_so);
    }
    cursor += pmatch[0].rm_eo;
    *success = regexec(regex, cursor, *nmatch, pmatch, REG_NOTBOL);
  }
}

void part_2(int const flags[grep_flag_size], int line_number,
            const char *buffer) {
  if (!flags[C] && !flags[L]) {
    if (flags[N]) {
      printf("%d:", line_number);
    }
    printf("%s", buffer);
    if (buffer[strlen(buffer) - 1] != '\n') {
      printf("\n");
    }
  }
}

void flag_C(int const flags[grep_flag_size], int files_quantity,
            int line_number, int i, char **argv, int count_lines) {
  if (flags[C]) {
    if (files_quantity > 1 && !(flags[H])) {
      printf("%s:", argv[i]);
      if (flags[N]) {
        printf("%d:", line_number);
      }
    }
    if (flags[L] && count_lines) {
      printf("1\n");
    } else {
      printf("%d\n", count_lines);
    }
  }
}