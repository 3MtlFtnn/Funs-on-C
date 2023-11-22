FLAGS = -Wall -Werror -Wextra -std=c11
CC = gcc

all: s21_cat

s21_cat: cat.o
	$(CC) $(FLAGS) -o cat cat.o

cat.o: s21_cat.c
	$(CC) $(FLAGS) -c s21_cat.c -o cat.o

clean:
	rm -f cat cat.o

rebuild: clean all