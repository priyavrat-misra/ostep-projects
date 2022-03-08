#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 100

int main(int argc, char *argv[]) {
	char buffer[BUFFER_SIZE];
	FILE *fp;
	while (--argc) {
		fp = fopen(*++argv, "r");
		if (fp == NULL) {
			printf("wcat: cannot open file\n");
			// or a better choice: perror("wcat");
			exit(1);
		}

		while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
			printf("%s", buffer);

		fclose(fp);
	}
	return 0;  // or exit(0)
}
