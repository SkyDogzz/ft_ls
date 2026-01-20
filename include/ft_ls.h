#ifndef FT_LS__H
#define FT_LS__H

#include <ctype.h>
#include <dirent.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#ifdef DEBUG
#define DEBUG_FLAG 1
#define DEBUG_FOLDER 1
#else
#define DEBUG_FLAG 0
#define DEBUG_FOLDER 0
#endif

typedef struct LS_Flag {
  unsigned char help : 1;
  unsigned char l : 1;
  unsigned char R : 1;
  unsigned char a : 1;
  unsigned char r : 1;
  unsigned char t : 1;
} LS_Flag;

void parse_flags(LS_Flag *flags, char **argv);
void init_flags(LS_Flag *flags);

size_t count_folders(char **argv);
char **parse_folder(char **argv);

typedef struct Leaf {
  size_t child_count;
  struct dirent *dirinfo;
  struct Leaf *childs;
} Leaf;

#endif
