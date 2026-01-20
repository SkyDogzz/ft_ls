#include "ft_ls.h"
#include <dirent.h>
#include <stdlib.h>

Leaf *leaf_create(void) {
  Leaf *leaf;

  leaf = (Leaf *)malloc(sizeof(Leaf));
  if (!leaf)
    return NULL;
  leaf->child_count = 0;
  leaf->childs = NULL;
  leaf->dirinfo = NULL;
  return leaf;
}

void free_leafs(Leaf **leaf) {
  int i = 0;
  while (leaf[i]) {
    free(leaf[i]);
    i++;
  }
  free(leaf);
}

Leaf **leaf_bulk_create(size_t count) {
  Leaf **leafs;
  size_t i = 0;

  if (count == 0)
    return NULL;
  leafs = (Leaf **)malloc(sizeof(Leaf *) * (count + 1));
  if (!leafs)
    return NULL;
  leafs[count] = NULL;
  while (i < count) {
    leafs[i] = leaf_create();
    if (!leafs[i])
      free_leafs(leafs);
    i++;
  }
  return leafs;
}

char *tolower_str(char *str) {
  int i = 0;
  while (str[i]) {
    if (str[i] >= 'A' && str[i] <= 'Z')
      str[i] += 32;
    i++;
  }
  return str;
}

int cmp(char *s1, char *s2) {
  while (*s1 && *s1 == '.')
    s1++;
  while (*s2 && *s2 == '.')
    s2++;
  return strcmp(tolower_str(s1), tolower_str(s2));
}

void sort_child(Leaf *root) {
  void *tmp;
  for (size_t i = 0; i < root->child_count; i++) {
    if (strcmp(root->childs[i]->dirinfo->d_name, ".") == 0 && i != 0) {
      tmp = root->childs[i];
      root->childs[i] = root->childs[0];
      root->childs[0] = tmp;
    }
    if (strcmp(root->childs[i]->dirinfo->d_name, "..") == 0 && i != 1) {
      tmp = root->childs[i];
      root->childs[i] = root->childs[1];
      root->childs[1] = tmp;
    }
  }
  for (size_t i = 2; i < root->child_count; i++) {
    for (size_t j = 2; j < root->child_count; j++) {
      if (i != j) {
        if (cmp(root->childs[i]->dirinfo->d_name,
                root->childs[j]->dirinfo->d_name) < 0) {
          tmp = root->childs[i];
          root->childs[i] = root->childs[j];
          root->childs[j] = tmp;
        }
      }
    }
  }
}

bool is_hidden(struct dirent dirinfo) { return dirinfo.d_name[0] == '.'; }

void print_dir(Leaf *root, LS_Flag flags) {
  size_t i = 0;

  if (!flags.r) {
    while (i < root->child_count) {
      if (root && root->childs && root->childs[i] && root->childs[i]->dirinfo) {
        if (!flags.a) {
          if (!is_hidden(*root->childs[i]->dirinfo) == true)
            printf("%s  ", root->childs[i]->dirinfo->d_name);
        } else
          printf("%s  ", root->childs[i]->dirinfo->d_name);
      }
      i++;
    }
  } else {
    i = root->child_count - 1;
    while ((int)i >= 0) {
      if (root && root->childs && root->childs[i] && root->childs[i]->dirinfo) {
        if (!flags.a) {
          if (!is_hidden(*root->childs[i]->dirinfo) == true)
            printf("%s  ", root->childs[i]->dirinfo->d_name);
        } else
          printf("%s  ", root->childs[i]->dirinfo->d_name);
      }
      i--;
    }
  }
  if (!flags.l)
    printf("\n");
}
