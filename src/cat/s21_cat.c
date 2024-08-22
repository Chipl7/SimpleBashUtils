#include "s21_cat.h"

int main(int argc, char **argv) {
  go_cat(argc, argv);
  return 0;
}

void go_cat(int argc, char **argv) {
  struct Flags flag = {0};
  int fileStartMark = 1;
  find_flag_cat(&flag, argc, &fileStartMark, argv);
  check_struct(&flag);
  openFiles_cat(&flag, fileStartMark, argc, argv);
}

void find_flag_cat(struct Flags *flag, int argc, int *fileStartMark,
                   char **argv) {
  int opt, option_index;
  struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                  {"number", 0, 0, 'n'},
                                  {"squeeze-blank", 0, 0, 's'},
                                  {0, 0, 0, 0}};
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      while ((opt = getopt_long(argc, argv, "+benstvTE", long_options,
                                &option_index)) != -1) {
        check_flags(flag, opt);
      }
    } else {
      *fileStartMark = i;
      break;
    }
  }
}

void check_flags(struct Flags *flag, int opt) {
  switch (opt) {
    case 'b':
      flag->b = 1;
      break;
    case 'e':
      flag->e = 1;
      flag->v = 1;
      break;
    case 'E':
      flag->e = 1;
      break;
    case 'n':
      flag->n = 1;
      break;
    case 's':
      flag->s = 1;
      break;
    case 't':
      flag->t = 1;
      flag->v = 1;
      break;
    case 'T':
      flag->t = 1;
      break;
    case 'v':
      flag->v = 1;
      break;
    default:
      fprintf(stderr, "unknown option");
      exit(1);
  }
}

void check_struct(struct Flags *flag) {
  if (flag->b == 1 && flag->n == 1) flag->n = 0;
}

void openFiles_cat(struct Flags *flag, int fileStartMark, int argc,
                   char **argv) {
  flag->str_number = 1;
  flag->file_numbers = 1;
  for (int i = fileStartMark; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    if (file == NULL) {
      printf("cat: %s: No such file or directory", argv[i]);
      continue;
    } else {
      print_file_cat(file, flag);
      fclose(file);
    }
    flag->file_numbers++;
  }
}

void print_file_cat(FILE *file, struct Flags *flag) {
  char prevCh, ch, nextCh;

  ch = fgetc(file);

  if (ch == EOF) return;
  if (flag->s == 1 && ch == '\n') {
    putchar(ch);
    while (ch == '\n' || ch == EOF) {
      ch = fgetc(file);
    }
  }
  if (flag->file_numbers < 2) {
    if (flag->n == 1) printf("%6d\t", flag->str_number++);
    if (flag->b == 1 && ch != '\n') printf("%6d\t", flag->str_number++);
  }
  while ((nextCh = fgetc(file)) != EOF) {
    write_character_to_console(flag, prevCh, ch, nextCh);
    prevCh = ch;
    ch = nextCh;
  }
  write_character_to_console(flag, prevCh, ch, nextCh);
}

void write_character_to_console(struct Flags *flag, char prevCh, char ch,
                                char nextCh) {
  if (s_mode(flag, prevCh, ch, nextCh) == 1) return;
  if (t_mode(flag, ch) == 1) return;
  e_mode(flag, ch);
  v_mode(flag, &ch);
  putchar(ch);
  n_mode(flag, ch, nextCh);
  b_mode(flag, ch, nextCh);
}

int s_mode(struct Flags *flag, char prevCh, char ch, char nextCh) {
  if (flag->s == 1 && (prevCh == '\n') && ch == '\n' && nextCh == '\n')
    return 1;
  return 0;
}

void e_mode(struct Flags *flag, char ch) {
  if (ch == '\n' && flag->e == 1) putchar('$');
}

int t_mode(struct Flags *flag, char ch) {
  if (ch == '\t' && flag->t == 1) {
    printf("^");
    printf("I");
    return 1;
  }
  return 0;
}

void v_mode(struct Flags *flag, char *ch) {
  if (flag->v == 1 && *ch != '\n' && *ch != '\t') {
    if (*ch >= 0 && *ch <= 31) {
      printf("^");
      *ch += 64;
    }
    if (*ch == 127) {
      printf("^");
      *ch = '?';
    }
    if (*ch > -128 && *ch < -96) {
      printf("M-^");
      *ch += 64 + 128;
    }
  }
}

void n_mode(struct Flags *flag, char ch, char nextCh) {
  if (ch == '\n' && flag->n == 1 && nextCh != EOF) {
    printf("%6d\t", flag->str_number);
    flag->str_number++;
  }
}

void b_mode(struct Flags *flag, char ch, char nextCh) {
  if (flag->b == 1 && ch == '\n' && nextCh != '\n' && nextCh != EOF) {
    printf("%6d\t", flag->str_number);
    flag->str_number++;
  }
}
