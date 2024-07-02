#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

struct Flags {
  int b;
  int e;
  int E;
  int n;
  int s;
  int t;
  int T;
  int v;
};

void go_cat(int argc, char **argv);
void find_flag_cat(struct Flags *flag, int argc, int *fileStartMark,
                   char **argv);
void check_flags(struct Flags *flag, int opt);
void check_struct(struct Flags *flag);
void openFiles_cat(struct Flags *flag, int fileStartMark, int argc,
                   char **argv);
void print_file_cat(FILE *file, struct Flags *flag);
void write_character_to_console(struct Flags *flag, int *strNumber, char prevCh,
                                char ch, char nextCh);
int s_mode(struct Flags *flag, char prevCh, char ch, char nextCh);
void e_mode(struct Flags *flag, char ch);
int t_mode(struct Flags *flag, char ch);
void v_mode(struct Flags *flag, char *ch);
void n_mode(struct Flags *flag, int *strNumber, char ch, char nextCh);
void b_mode(struct Flags *flag, int *strNumber, char ch, char nextCh);
