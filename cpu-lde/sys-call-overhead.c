#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
  const int ITERATIONS = 10000000;
  unsigned int tdiff_nsecs;
  int i;

  struct timespec tp1, tp2;

  clock_gettime(0, &tp1);

  for (i = 0; i < ITERATIONS; i++) {
    if (read(STDIN_FILENO, NULL, 0) < 0) {
      fprintf(stderr, "failed to read from stdin\n");
      exit(1);
    }
  }

  clock_gettime(0, &tp2);

  tdiff_nsecs = ((tp2.tv_sec - tp1.tv_sec) * 1000000000) + tp2.tv_nsec - tp1.tv_nsec;

  printf("time taken to execute sys calls was %dns\n", tdiff_nsecs);
  printf("avg time taken to execute sys call was %fns\n", (float) tdiff_nsecs / ITERATIONS);

  return 0;
}
