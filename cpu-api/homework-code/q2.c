#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  int rc;
  int fd = open("q2-file", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

  rc = fork();

  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    if (write(fd, "Hello, child!\n", 14) < 0) {
      fprintf(stderr, "Child write failed\n");
    }

    printf("Child wrote successfully\n");
  } else {
    if (write(fd, "Hello, parent!\n", 15) < 0) {
      fprintf(stderr, "Parent write failed\n");
    }

    printf("Parent wrote successfully\n");
  }

  return 0;
}
