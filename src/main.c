#include "ft_ls.h"

int main(int argc, char **argv) {
  LS_Flag flags;
  char **folder;

  init_flags(&flags);
  parse_flags(&flags, argv);

  folder = parse_folder(argv);

  return EXIT_SUCCESS;
  (void)argc;
  (void)argv;
  (void)folder;
}
