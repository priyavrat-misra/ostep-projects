#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define q 101  // a prime number

int compute_hash(char *word, int n) {
	int i, h = 0, d = 1 << 8*sizeof(char);
	for (i = 0; i < n; ++i)
		h = (h * d + word[i]) % q;
	return h;
}

void print_if_contains(char *word, int n, int ph, char *line, int len) {
	// Rabin Karp string matching algorithm
	if (len >= n) {
		int msv = 1;
		int i, j, d = 1 << 8*sizeof(char);

		// msv will be multiplied to the most significant char
		for (i = 0; i < n - 1; ++i)  // msv = pow(d, n - 1) % q
			msv = (msv * d) % q;

		int th = compute_hash(line, n); // hash for 1st window of text
		for (i = 0; i < len - n + 1; ++i) {
			if (ph == th) {
				for (j = 0; j < n; ++j) {
					if (word[j] != line[i+j])
						break;
				}
				if (j == n) {
					fwrite(line, len, 1, stdout);
					return;
				}
			}
			// (a*b)%c = (a%c * b%c)%c
			th = (((th - line[i]*msv % q)*d % q) + line[i+n]) % q;
		}
	}
	return;
}

int main(int argc, char *argv[]) {
	FILE *stream;
	if (argc == 2) {
		stream = stdin;
	} else if (argc == 3) {
		stream = fopen(argv[2], "r");
		if (stream == NULL) {
			printf("wgrep: cannot open file\n");
			exit(1);
		}
	} else {
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}

	ssize_t nread;  // or long signed int nread; 
	size_t len = 0;  // or long unsigned int len = 0;;
	char *line = NULL; // or (char*) malloc(len);
	int n = strlen(argv[1]);
	int ph = compute_hash(argv[1], n);  // pattern hash

	while ((nread = getline(&line, &len, stream)) != -1)
		print_if_contains(argv[1], n, ph, line, nread);

	free(line);
	fclose(stream);
	exit(0);
}
