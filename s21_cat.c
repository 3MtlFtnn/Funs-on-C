#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define BUFF 1024

void print_file_cout(const char* name);
int count_simb(const char* name);
void print(const char* name);
void printNotNUll(const char* name);


int main(int argc, char* argv[]) {
  // print_file(argv[2]);
  int opt;

  //Считаем кол-во симвволов (НЕ РАБОТАЕТ!) неправильно argv
  // int counter = count_simb(argv[2]);
  // printf("Counter: %d\n",counter);

  //массивчик для символов
  // char* buff=(char*)malloc(counter*sizeof(char));

  FILE* file = NULL;
  while ((opt = getopt(argc, argv, "bn")) != -1 || opt == -1) {
    switch (opt) {
      case 'n':
        for (int i = optind; i < argc; i++) {
          file = fopen(argv[i], "r");
          if (file == NULL) {
            fprintf(stderr, "Cant open file: %s", argv[i]);
          }
          print_file_cout(argv[i]);
        }
        break;
      case 'b':
        for (int i = optind; i < argc; i++) {
          file = fopen(argv[i], "r");
          if (file == NULL) {
            fprintf(stderr, "Cant openn %s", argv[i]);
          }
          printNotNUll(argv[i]);
        }
        break;
      default:
        print(argv[1]);
        // free(buff);
        return 0;
    }
  }

  // free(buff);
  return 0;
}

//функция ростого вывода содержимого
void print(const char* name) {
  FILE* file = fopen(name, "rt");
  if (file == NULL) {
    // fprintf(stderr, "Null file");
    return;
  } else {
    int c = fgetc(file);
    while (c != EOF) {
      putc(c, stdout);
      c = fgetc(file);
    }
  }
  fclose(file);
}

// Функция для вывода содержимого файла с подсчетом
void print_file_cout(const char* name) {
  FILE* f = fopen(name, "rt");

  if (f != NULL) {
    int chr = fgetc(f);
    int count = 1;
    printf("%d ", count);
    while (chr != EOF) {
      putc(chr, stdout);
      if (chr == '\n') {
        count++;
        printf("%d ", count);
      }
      chr = fgetc(f);
    }
    fclose(f);
  }
}

//Функция для подсчета непустых строк
void printNotNUll(const char* name) {
    FILE* file = fopen(name, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return;
    }

    int lineNumber = 1;
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        int lineLength = strlen(line);
        int isEmptyLine = 1;

        for (int i = 0; i < lineLength; i++) {
            if (!isspace(line[i])) {
                isEmptyLine = 0;
                break;
            }
        }

        if (!isEmptyLine) {
            printf("%d ", lineNumber);
            lineNumber++;
        }

        printf("%s", line);
    }

    fclose(file);
}


// Функция для счета символов
int count_simb(const char* name) {
  FILE* f = fopen(name, "rt");
  int c = fgetc(f);
  int count = 0;
  while (c != EOF) {
    c = fgetc(f);
    count++;
  }
  fclose(f);
  return count;
}
