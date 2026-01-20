#include "ft_ls.h"

void print_flags(LS_Flag *flags) {
  printf("\n\n--------------------\n");
  printf("flags:\n");
  printf("help %d:\n", flags->help);
  printf("l %d:\n", flags->l);
  printf("R %d:\n", flags->R);
  printf("a %d:\n", flags->a);
  printf("r %d:\n", flags->r);
  printf("t %d:\n", flags->t);
  printf("--------------------\n\n");
}

void init_flags(LS_Flag *flags) {
  flags->help = 0;
  flags->l = 0;
  flags->R = 0;
  flags->a = 0;
  flags->r = 0;
  flags->t = 0;
}

void parse_flags(LS_Flag *flags, char **argv) {
  size_t len;

  argv++;
  while (*argv) {
    len = strlen(*argv);
    if (len <= 1) {
      argv++;
      continue;
    }
    if (strncmp(*argv, "--help", 6) == 0)
      flags->help = true;
    else if (*argv[0] == '-') {
      (*argv)++;
      while (**argv && isalpha(**argv)) {
        if (**argv == 'l')
          flags->l = true;
        else if (**argv == 'R')
          flags->R = true;
        else if (**argv == 'a')
          flags->a = true;
        else if (**argv == 'r')
          flags->r = true;
        else if (**argv == 't')
          flags->t = true;
        (*argv)++;
      }
    }
    argv++;
  }

  if (DEBUG_FLAG)
    print_flags(flags);
}
