#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <getopt.h>

#define LINE_LENGTH 1024

int add_arg_patterns(const char *file, const char *arg);

// Начало
int main(int argc, char *argv[]) {

	int c = 0;
	char *context = NULL;

	while ((c = getopt(argc, argv, "e:")) != -1) {
		switch (c) {
			case 'e':
				context = optarg;
				add_arg_patterns(argv[optind], context);
				break;
		}
	}

	return 0;
}

// Флаг -e
int add_arg_patterns(const char *file, const char *arg) {
	FILE *fp = fopen(file, "r");
	if (fp == NULL) {
		fprintf(stderr, "Can't open file %s\n", file);
		return 1;
	}

	int line_number = 0;
	char line[LINE_LENGTH];

	while (fgets(line, sizeof(line), fp)) {
		line_number++;

		if (arg != NULL && strstr(line, arg) != NULL) {
			printf(line);
		}
	}

	fclose(fp);
	return 0;
}
