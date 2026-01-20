#include "ft_ls.h"

int main(int argc, char **argv) {
  LS_Flag flags;
  char **folder;
  DIR *dir;
  Leaf *root;
  size_t count;
  struct dirent *dirinfo;
  size_t i = 0;

  init_flags(&flags);
  parse_flags(&flags, argv);

  folder = parse_folder(argv);

  if (!folder || !folder[0])
    return EXIT_FAILURE;

  dir = opendir(folder[0]);
  if (dir) {
    root = leaf_create();
    count = 0;
    while (true) {
      dirinfo = readdir(dir);
      if (!dirinfo)
        break;
      count++;
    }
    closedir(dir);
    dir = opendir(folder[0]);
    if (dir) {
      root->childs = leaf_bulk_create(count);
      root->child_count = count;
      while (i < count) {
        dirinfo = readdir(dir);
        if (!dirinfo)
          break;
        root->childs[i]->dirinfo = dirinfo;
        i++;
      }
    }
    sort_child(root);
    print_tree(root);
  }

  return EXIT_SUCCESS;
  (void)argc;
  (void)argv;
  (void)folder;
}
