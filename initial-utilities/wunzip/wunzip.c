#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc <= 1) {
		printf("wunzip: file1 [file2 ...]\n");
		exit(EXIT_FAILURE);
	}
	FILE *fp;
	int no, ch, i;
	while (--argc) {
		if ((fp = fopen(*++argv, "r")) == NULL) {
			printf("wunzip: cannot open file");
			exit(EXIT_FAILURE);
		}
		while (1) {
			if (!fread(&no, sizeof(int), 1, fp)) break;
			fread(&ch, sizeof(char), 1, fp);
			for (i = 0; i < no; ++i)
				printf("%c", ch);
		}
		fclose(fp);
	}
	exit(EXIT_SUCCESS);
}
