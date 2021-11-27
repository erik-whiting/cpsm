#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void print_numbers(int counter);

int main() {
  for (int i = 1; i <= 3; i++) {
    int pid = fork();
    if (pid == 0) {
      print_numbers(i);
    }
  }

  return 0;
}

void print_numbers(int counter) {
  counter--;
  int min = (counter * 100) + 1;
  int max = min + 98;
  for (int i = max; i >= min; i-=2) { printf("%d\n", i); }
}