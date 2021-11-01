#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char msg[7];
  struct flock lock;

  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = 0;

  char *printedMsg = "printed";
  int fd = open("q3.lock", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    lock.l_type = F_WRLCK;
    if (fcntl(fd, F_SETLKW, &lock) < 0) {
      fprintf(stderr, "fcntl failed to set lock\n");
      exit(1);
    }

    printf("hello\n");
    write(fd, printedMsg, strlen(printedMsg));
  } else {
    while (strcmp(msg, printedMsg) != 0) {
      lock.l_type = F_RDLCK;
      if (fcntl(fd, F_SETLK, &lock) < 0) {
        continue;
      }

      lseek(fd, 0, SEEK_SET);

      if (read(fd, msg, strlen(printedMsg)) < 0) {
        fprintf(stderr, "failed to read q3.lock\n");
        exit(1);
      }

      lock.l_type = F_UNLCK;
      if (fcntl(fd, F_SETLK, &lock) < 0) {
        fprintf(stderr, "fcntl failed to release lock\n");
        exit(1);
      }

      if (strcmp(msg, printedMsg) == 0) {
        printf("goodbye\n");
      }
    }
  }

  return 0;
}
