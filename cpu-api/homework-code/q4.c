#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    execlp("ls", "q4", "-l", "/home/markd/", NULL);
  } else {
    printf("parent says hello\n");
  }

  return 0;
}
