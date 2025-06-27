#include "s21_cat.h"

int main(int argc, char **argv) {
  int flags[cat_flag_size] = {0};

  if (parse_args(argc, argv, flags)) {
    main_loop(flags, argv, argc);
  }

  return 0;
}

int parse_args(int argc, char **argv, int *flags) {
  int num = 0;
  int is_valid = true;
  int lng_ind;
  while ((num = getopt_long(argc, argv, "beEnstTv", long_options, &lng_ind)) !=
             -1 &&
         is_valid) {
    switch (num) {
      case 'b':
        flags[B]++;
        break;
      case 'e':
        flags[E]++;
        flags[V]++;
        break;
      case 'E':
        flags[E]++;
        break;
      case 'n':
        flags[N]++;
        break;
      case 'v':
        flags[V]++;
        break;
      case 's':
        flags[S]++;
        break;
      case 't':
        flags[T]++;
        flags[V]++;
        break;
      case 'T':
        flags[T]++;
        break;
      default:
        is_valid = false;
        break;
    }
  }
  if (flags[B]) {
    flags[N] = 0;
  }

  return is_valid;
}

void main_loop(int const flags[cat_flag_size], char **argv, int argc) {
  char c;
  int count_lines = 1;
  int empty_line = 0;
  int new_line = true;
  int flag_S = false;

  for (int i = optind; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (f == NULL) {
      fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
    } else {
      while (fscanf(f, "%c", &c) != EOF) {
        if (flags[S]) {
          flagS(&c, &empty_line, &flag_S);
        }
        if (flags[B] && new_line && c != '\n' && !flag_S) {
          printf("%6d\t", count_lines);
          count_lines++;
          new_line = false;
        }
        if (flags[N] && new_line && !flag_S) {
          printf("%6d\t", count_lines);
          count_lines++;
          new_line = false;
        }
        if (flags[T] && c == '\t' && !flag_S) {
          printf("^");
          c = 'I';
        }
        if (flags[E] && c == '\n' && !flag_S) {
          printf("$");
        }
        if (flags[V] && c != '\n' && c != '\t') {
          flagV(&c);
        }
        if (c == '\n') {
          new_line = true;
        }
        if (!flag_S) {
          fprintf(stdout, "%c", c);
        }
        flag_S = false;
      }
    }
    fclose(f);
  }
}

int flagV(char *c) {
  if (*c >= 0 && *c <= 31) {
    printf("^");
    *c += 64;
  } else if (*c == 127) {
    printf("^");
    *c -= 64;
  } else if (*c < 0) {
    printf("M-");
    unsigned char u = (unsigned char)*c;
    if (u < 128 + 32) {
      printf("^");
      u = u - 128 + 64;
    } else if (u < 255) {
      u -= 128;
    } else {
      printf("^");
      u = u - 128 - 64;
    }
    *c = (char)u;
  }
  return *c;
}

void flagS(const char *c, int *empty_line, int *flag_S) {
  if (*c == '\n') {
    *empty_line += 1;
    if (*empty_line > 2) {
      *flag_S = true;
    }
  } else {
    *empty_line = 0;
  }
}