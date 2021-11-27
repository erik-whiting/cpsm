#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void print_numbers(int counter);

int main() {
  int counter = 0;
  int parent = getpid();
  int pid = fork();

  if (pid == 0) {
    // child
    counter++;
    printf("Child\n");
    if (fork() == 0) {
      // Grandchild
      counter++;
      printf("Grandchild\n");
      print_numbers(counter);
    } else { print_numbers(counter); }
  } else {
    // parent
    print_numbers(counter);
  }

  return 0;
}

void print_numbers(int counter) {
  int min = (counter * 100) + 1;
  int max = min + 98;

  for (int i = max; i >= min; i-=2) { printf("%d\n", i); }
}
