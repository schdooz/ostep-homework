#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  const int BSIZE = 100;
  char buf[BSIZE];
  int fildes[2];

  if (pipe(fildes) < 0) {
    fprintf(stderr, "failed to create pipe\n");
    exit(1);
  }

  int rc1 = fork();

  if (rc1 < 0) {
    fprintf(stderr, "failed to fork\n");
    exit(1);
  } else if (rc1 == 0) { // first child (writer)
    close(fildes[0]);

    if (dup2(fildes[1], STDOUT_FILENO) < 0) {
      fprintf(stderr, "failed to duplicated fildes[1] to stdout\n");
      exit(1);
    }

    printf("Hello, sibling\n");
    close(fildes[1]);
  } else {
    int rc2 = fork();

    if (rc2 < 0) {
      fprintf(stderr, "failed to fork\n");
      exit(1);
    } else if (rc2 == 0) { // second child (reader)
      close(fildes[1]);

      dup2(fildes[0], STDIN_FILENO);
      read(STDIN_FILENO, buf, BSIZE);

      printf("reader sibling read %s", buf);
      close(fildes[0]);
    } else { // parent
      close(fildes[0]);
      close(fildes[1]);
    }
  }

  return 0;
}
