#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int x = 1;
  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    x = 0;
    printf("child process, x is %d\n", x);
  } else {
    x = rc;
    printf("parent process, x is %d\n", x);
  }

  return 0;
}
