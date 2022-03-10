#include <stdio.h>
#include <stdlib.h>

void print(int sum, int ch) {
	//printf("%d%c", sum, ch); // for debugging
	fwrite(&sum, sizeof(int), 1, stdout);
	putc(ch, stdout); //or fwrite(&ch, sizeof(char), 1, stdout);
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		printf("wzip: file1 [file2 ...]\n");
		exit(EXIT_FAILURE);
	}
	FILE *fp;
	int t, c, s = 1, n = argc;
	while (--n) {
		if ((fp = fopen(*++argv, "r")) == NULL) {
			printf("wzip: cannot open file\n");
			exit(EXIT_FAILURE);
		}
		c = getc(fp);

		// condition to check if some word
		// spans across multiple files (1)
		// should take effect from 2nd file onwards
		if (n < argc-1) {
			if (t == c) ++s;
			else {
				print(s, t);
				s = 1;
			}
		}

		while (c != EOF) {
			while ((t = getc(fp)) == c)
				++s;

			// this preceeds (1)
			// n!=1 to deal with the last file
			if (n != 1 && t == EOF) {
				t = c;
				break;
			}

			print(s, c);
			c = t;
			s = 1;
		}
		fclose(fp);
	}
	exit(EXIT_SUCCESS);
}
