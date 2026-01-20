#include "ft_ls.h"

void print_folder(char **folder) {
  printf("\n\n--------------------\n");
  printf("folders:\n");
  while (*folder) {
    printf("%s\n", *folder);
    folder++;
  }
  printf("--------------------\n\n");
}

size_t count_folders(char **argv) {
  size_t count = 0;

  argv++;
  while (*argv) {
    if (strlen(*argv) > 0 && *argv[0] != '-')
      count++;
    argv++;
  }
  return count;
}

static void free_tab(char **folder) {
  int i = 0;

  while (folder[i]) {
    free(folder[i]);
    i++;
  }
  free(folder);
}

char **parse_folder(char **argv) {
  char **folder;
  bool act = false;
  size_t count = count_folders(argv);
  int i = 0;

  if (count == 0) {
    act = true;
    count = 1;
  }
  folder = (char **)malloc(sizeof(char *) * (count + 1));
  if (!folder)
    return NULL;
  if (act) {
    folder[0] = strdup(".");
    folder[1] = NULL;
    if (!folder[0]) {
      free_tab(folder);
      return NULL;
    }
    return folder;
  }
  argv++;
  while (*argv) {
    if (strlen(*argv) > 0 && (*argv)[0] != '-') {
      folder[i] = strdup(*argv);
      if (!folder[i]) {
        free_tab(folder);
        return NULL;
      }
      i++;
    }
    argv++;
  }
  if (DEBUG_FOLDER)
    print_folder(folder);
  return folder;
}
