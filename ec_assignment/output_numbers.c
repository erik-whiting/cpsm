#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	FILE *f;
	int line;
	int max_file_lines = 10;

	f = fopen("./numbers", "r");
	int iterations = 0;
	int collect_numbers = 0;
	int product = 1;
	while (iterations < max_file_lines) {
		if (fscanf(f, "%d", &line) == 1) {
			iterations++;
			collect_numbers++;
			product *= line;
		}
		else {
			sleep(1);
			clearerr(f);
		}
		if (collect_numbers == 3) {
			printf("Product of last three numbers: %d\n", product);
			collect_numbers = 0;
			product = 1;
		}
	}
	return 0;
}
