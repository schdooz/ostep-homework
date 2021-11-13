#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    close(STDOUT_FILENO);
    // fails to print since STDOUT_FILENO file descriptor is closed.
    printf("Trying to write to stdout...\n");
  } else {
    printf("I'm the parent.\n");
  }

  return 0;
}
