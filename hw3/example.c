#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int parent_id = getpid();
  printf("Parent PID: %d\n", parent_id);

  int pid = fork();
  printf("Current PID: %d\n", pid);

  if (pid == 0) {
    printf("pid == 0, actual pid is %d, getpid() is: %d\n", pid, getpid());
  } else {
    printf("pid != 0, actual pid is %d, getpid() is: %d\n", pid, getpid());
  }

  return 0;
}