#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	printf("Printing before first fork\n");
	int t = fork();
	
	if (t != 0) {
		printf("Printing from first forked process, PID %d\n", t);
	}
	
	if (t == 0) {
		printf("Printing after first fork from parent process, PID %d\n", t);
	}
	
	int t2 = fork();
	if (t2 != 0 && t != 0) {
		printf("Printing after second fork from process %d\n", t2);
	}
	printf("Printing output that doesn't depend on t\n");
	return 0;
}
