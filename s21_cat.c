#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>


void print_file_cout(const char* name);
void print(const char* name);
void printNotNUll(const char* name);
void print_dollar(const char* name);
void print_spaces(const char* name);
void print_tab(const char* name);


int main(int argc, char* argv[]) {
  int opt;

  FILE* file = NULL;
  while ((opt = getopt(argc, argv, "bnest")) != -1 || opt == -1) {
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
			case 'e':
				for(int i = optind; i<argc; i++){
					file = fopen(argv[i], "r");
					if(file==NULL){
						fprintf(stderr, "Cant open %s", argv[i]);
					}
					print_dollar(argv[i]);
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
			case 's':
				for(int i = optind; i < argc; i++){
					file = fopen(argv[i], "r");
					if(file==NULL){
						fprintf(stderr, "Cant open this parament %s", argv[i]);
					}
					print_spaces(argv[i]);
				}
				break;
			case 't':
				for(int i = optind; i < argc; i++){
					file = fopen(argv[i], "r");
					if (file==NULL){
						fprintf(stderr, "Cant opeen parament %s", argv[i]);
					}
					print_tab(argv[i]);
				}
				break;
			default:
        print(argv[1]);
        return 0;
    }
  }

  return 0;
}

//функция для слияния нескольких пустых строк
void print_spaces(const char* name) {
    FILE* file = fopen(name, "rt");
    if (file == NULL) {
        fprintf(stderr, "Can't open file\n");
        return;
    }

    char buffer[1488];
    int emptyLineCount = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        int length = strlen(buffer);

        int isEmptyLine = 1;
        for (int i = 0; i < length; i++) {
            if (!isspace(buffer[i])) {
                isEmptyLine = 0;
            }
        }

        // Если строка не пустая, выводим ее и сбрасываем счетчик пустых строк
        if (!isEmptyLine) {
            fputs(buffer, stdout);
            emptyLineCount = 0;
        }
        // Если строка пустая и предыдущая строка тоже была пустой, пропускаем ее
        else if (emptyLineCount > 0) {
            continue;
        }
        else {
            fputs(buffer, stdout);
            emptyLineCount++;
        }
    }

    fclose(file);
}

				
//функция для вывода содержимого файла, в конце ставится '$'
void print_dollar(const char* name){
	FILE* file = fopen(name, "rt");
	if(file == NULL){
		printf("Error open file");
	}
	char buf[1024];
	while(fgets(buf, sizeof(buf), file)){
		int lineLenght = strlen(buf);
		for(int i = 0; i<lineLenght; i++){
			if(buf[i]=='\n'){
				printf("$\n");
			}else{
				putc(buf[i], stdout);
			}
		}
	}
	fclose(file);
}

//Функция ставит в конце '$' и табы отмечает '^I'
void print_tab(const char* name){
	FILE* file = fopen(name, "rt");
	if(file==NULL){
		printf("Error open this file");
	}
	char buffer[1024];
	while(fgets(buffer, sizeof(buffer),file)){
		int lenght = strlen(buffer);
		for(int i = 0; i<lenght; i++){
			if(buffer[i]=='\t'){
				buffer[i]='^';
				printf("^I");
			}else if(buffer[i]=='\n'){
				printf("$\n");
			}else{
				putc(buffer[i], stdout);
			}
		}
	}
	fclose(file);
}


//функция ростого вывода содержимого
void print(const char* name) {
    FILE* file = fopen(name, "rt");
  
    if (file == NULL) {
        if (name != NULL) {
						return;
        } else {
					char ch;
					while (read(STDIN_FILENO, &ch, 1) > 0) {
						  putc(ch, stdout);
					}
				}
    } else {
        int c = fgetc(file);
        while (c != EOF) {
            putc(c, stdout);
            c = fgetc(file);
        }
        fclose(file);
    }
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
