#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Flags_grep {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  char pattern[1024];
  int e_patterns_count;
};

void go_grep(int argc, char **argv);
void argument_parcer(struct Flags_grep *flag, int argc, char **argv);
void patter_add(struct Flags_grep *flag, char *optarg);
void openFiles_grep(struct Flags_grep *flag, regex_t *reg, char *argv);
void add_reg_from_file(struct Flags_grep *flag, char *argv);
void o_mode(regex_t *reg, char *buffer);
void output_buffer(char *buffer, int read_line);
void s_mode_grep(FILE *file, struct Flags_grep *flag, char *argv);
void c_mode_and_l_mode(struct Flags_grep *flag, char *argv, int *count);
