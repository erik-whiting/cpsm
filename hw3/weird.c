#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int main_thread = getpid();
  printf("The main thread PID is: %d\n", main_thread);
  int proc_id = fork();

  if (proc_id == 0) {
    // I am the child process
    printf("Child PID: %d\n", getpid());
  } else {
    // I *should* be the parent process
    printf("Parent PID: %d\n", getpid());
  }

  return 0;
}