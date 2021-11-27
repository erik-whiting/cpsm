#include <stdio.h>


int main() {
	FILE *f = fopen("numbers", "w");
	if (f == NULL) {
		printf("Couldn't open file");
		return -1;
	}

	int user_input;
	for (int i = 0; i < 10; i++) {
		printf("Enter a number: ");
		scanf("%d", &user_input);
		fprintf(f, "%d\n", user_input);
	}

	fclose(f);
	return 0;
}
