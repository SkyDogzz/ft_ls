#include "ft_ls.h"

int main(int argc, char **argv) {
  LS_Flag flags;
  char **folder;
  DIR *dir;
  Leaf *root;
  size_t count;
  struct dirent *dirinfo;

  init_flags(&flags);
  parse_flags(&flags, argv);

  folder = parse_folder(argv);

  if (!folder || !folder[0])
    return EXIT_FAILURE;

  dir = opendir(folder[0]);
  if (dir) {
    count = 0;
    while (true) {
      dirinfo = readdir(dir);
      if (!dirinfo)
        break;
      count++;
    }
    closedir(dir);
    printf("%ld child", count);
  }
  (void)root;

  return EXIT_SUCCESS;
  (void)argc;
  (void)argv;
  (void)folder;
}
