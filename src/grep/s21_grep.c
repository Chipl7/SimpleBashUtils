#include "s21_grep.h"

int main(int argc, char **argv) {
  go_grep(argc, argv);
  return 0;
}

void go_grep(int argc, char **argv) {
  regex_t reg;
  struct Flags_grep flag = {0};
  argument_parcer(&flag, argc, argv);
  int error = regcomp(&reg, flag.pattern, REG_EXTENDED | flag.i);
  if (error > 0) {
    perror("Error");
  }
  for (int i = optind; i < argc; i++) {
    openFiles_grep(&flag, &reg, argv[i]);
  }
  regfree(&reg);
}

void argument_parcer(struct Flags_grep *flag, int argc, char **argv) {
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        flag->e = 1;
        patter_add(flag, optarg);
        break;
      case 'i':
        flag->i = REG_ICASE;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'f':
        flag->f = 1;
        add_reg_from_file(flag, optarg);
        break;
      case 'o':
        flag->o = 1;
        break;
      default:
        fprintf(stderr, "unknown option");
        exit(1);
    }
  }
  if (flag->e_patterns_count == 0) {
    patter_add(flag, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {
    flag->h = 1;
  }
}

void patter_add(struct Flags_grep *flag, char *optarg) {
  if (flag->e_patterns_count > 0) {
    strcat(flag->pattern, "|");
  }
  strcat(flag->pattern, "(");
  strcat(flag->pattern, optarg);
  strcat(flag->pattern, ")");
  flag->e_patterns_count++;
}

void openFiles_grep(struct Flags_grep *flag, regex_t *reg, char *argv) {
  FILE *file = fopen(argv, "r");
  s_mode_grep(file, flag, argv);
  char *buffer = NULL;
  size_t memlen = 0;
  int read_line = 0, strNumber = 1, count = 0;
  read_line = getline(&buffer, &memlen, file);
  while (read_line != -1) {
    int result = regexec(reg, buffer, 0, NULL, 0);
    if ((result == 0 && flag->v == 0) || (result != 0 && flag->v == 1)) {
      if (flag->c == 0 && flag->l == 0) {
        if (flag->h == 0) {
          printf("%s:", argv);
        }
        if (flag->n == 1) {
          printf("%d:", strNumber);
        }
        if (flag->o == 1) {
          o_mode(reg, buffer);
        } else
          output_buffer(buffer, read_line);
      }
      count++;
    }
    read_line = getline(&buffer, &memlen, file);
    strNumber++;
  }
  free(buffer);
  c_mode_and_l_mode(flag, argv, &count);
  fclose(file);
}

void add_reg_from_file(struct Flags_grep *flag, char *argv) {
  FILE *file = fopen(argv, "r");
  if (file == NULL) {
    if (flag->s == 0) {
      perror(argv);
    }
    exit(1);
  }
  char *buffer = NULL;
  size_t memlen = 0;
  int read_line = getline(&buffer, &memlen, file);
  while (read_line != -1) {
    if (buffer[read_line - 1] == '\n') {
      buffer[read_line - 1] = '\0';
    }
    patter_add(flag, buffer);
    read_line = getline(&buffer, &memlen, file);
  }
  free(buffer);
  fclose(file);
}

void o_mode(regex_t *reg, char *buffer) {
  regmatch_t match;
  int offset = 0;
  for (int i = 0;; i++) {
    if (regexec(reg, buffer + offset, 1, &match, 0)) break;
    int start = match.rm_so + offset;
    int end = match.rm_eo + offset;
    for (int i = start; i < end; i++) {
      putchar(buffer[i]);
    }
    putchar('\n');
    offset = end;
  }
}

void output_buffer(char *buffer, int read_line) {
  for (int i = 0; i < read_line; i++) {
    char x = buffer[i];
    putchar(x);
  }
  if (buffer[read_line - 1] != '\n') {
    putchar('\n');
  }
}

void s_mode_grep(FILE *file, struct Flags_grep *flag, char *argv) {
  if (file == NULL) {
    if (flag->s == 0) {
      perror(argv);
    }
    exit(1);
  }
}

void c_mode_and_l_mode(struct Flags_grep *flag, char *argv, int *count) {
  if (flag->c == 1 && flag->l == 0) {
    if (flag->h == 0) {
      printf("%s:", argv);
    }
    printf("%d\n", *count);
  }
  if (flag->l == 1 && flag->c == 0) {
    if (*count > 0) {
      printf("%s\n", argv);
    }
  }
  if (flag->l == 1 && flag->c == 1 && flag->h == 1) {
    printf("%d\n", *count);
    if (*count > 0) {
      printf("%s\n", argv);
    }
  }
}