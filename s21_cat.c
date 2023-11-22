#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "flags.h"
int readd(int argc,  char* argv[], flags* flag);
void out(char* fp, flags* flag);

int main(int argc, char* argv[]) {
  __attribute__((unused))int opt;
  __attribute__((unused))int opt_index = 0;
  int files_count;
  flags option = {0};
  files_count = readd(argc, argv, &option);

  if (option.error == 1) {
    fprintf(stderr, "Error!!!");
    return 1;
  } else {
    while (files_count < argc) {
      __attribute__((unused))char* fp;
      fp = argv[files_count];
      out(argv[files_count], &option);
      files_count++;
    }
  }

  return 0;
}

int readd(int argc,  char* argv[], flags* flag) {
  const struct option long_option[] = {
      {"number-nonblank", no_argument, 0, 'b'},
      {"squeeze-blank", no_argument, 0, 's'},
      {"number", no_argument, 0, 'n'},
      {"show-ends", no_argument, 0, 'e'},
  };
  int opt = 0;

  while ((opt = getopt_long(argc, argv, "beEnstTv?", long_option, NULL)) != -1) {
    switch (opt) {
      case 'b':
        flag->NN = 1;
        break;
      case 'e':
        flag->dollar = flag->vET = 1;
        break;
      case 'E':
        flag->dollar = 1;
        break;
      case 'n':
        flag->count = 1;
        break;
      case 's':
        flag->spaces = 1;
        break;
      case 't':
        flag->tab = flag->vET = 1;
        break;
      case 'T':
        flag->tab = 1;
        break;
      case 'v':
        flag->vET = 1;
        break;
      case '?':
        flag->error = 1;
        break;
    }
  }
  return optind;
}

void out(char* fp, flags* flag)
{
  FILE* file = fopen(fp, "r");
  if (file == NULL) {
    fprintf(stderr, "Error with opening file");
    return;
  }

  int ch;
  int prev = '\n';
  int current = 1;
  int squeeze = 0;
  while ((ch = fgetc(file)) != EOF) {
    if (flag->spaces == 1) {
      if (ch == '\n' && prev == '\n') {
        if (squeeze == 1) {
          continue;
        }
        squeeze++;
      } else {
        squeeze = 0;
      }
    }

    if (flag->NN == 1) {
      if (prev == '\n' && ch != '\n') {
        printf("%*d\t", 6, current);
        current++;
      }
    }

    if (flag->count == 1 && flag->NN == 0 && prev == '\n') {
      printf("%*d\t", 6, current);
      current++;
    }

    if (flag->dollar == 1 && ch == '\n') {
      putchar('$');
    }

    if (flag->tab == 1 && ch == '\t') {
      printf("^");
      ch = 'I';
    }

    if (flag->vET == 1) {
      if ((ch >= 0 && ch <= 31) && ch != '\t' && ch != '\n') {
        printf("^");
        ch = ch + 64;
      } else if (ch == 127) {
        printf("^");
        ch = ch - 64;
      }
    }
    if(flag->error == 1){
      
    }

    putchar(ch);
    prev = ch;
  }

  fclose(file);
}