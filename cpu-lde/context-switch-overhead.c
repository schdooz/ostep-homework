#define _POSIX_C_SOURCE 199309L
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main() {
  const int BUFSIZE = 100, ITERATIONS = 1000000;
  const int NO_CTXSW = (2 * ITERATIONS) - 1;
  int pipefd0[2], pipefd1[2], pipefd2[2], pipefd3[2];
  int pid, i;
  char *txt = "some data";
  char buf[BUFSIZE];
  struct timespec tp0, tp1, tp2, tp3;
  cpu_set_t cpu_set;

  // ensure processes run on same CPU
  CPU_SET(0, &cpu_set);
  sched_setaffinity(0, sizeof(cpu_set_t), &cpu_set);

  if (pipe(pipefd0) < 0 || pipe(pipefd1) || pipe(pipefd2) < 0 ||
      pipe(pipefd3) < 0) {
    fprintf(stderr, "unable to create pipes\n");
    exit(1);
  }

  // measure overhead of reading and writing to ring of pipes
  clock_gettime(0, &tp0);

  for (i = 0; i < ITERATIONS; i++) {
    write(pipefd0[1], txt, strlen(txt));
    write(pipefd1[1], txt, strlen(txt));
    read(pipefd1[0], buf, strlen(txt));
    read(pipefd0[0], buf, strlen(txt));
  }

  clock_gettime(0, &tp1);

  pid = fork();

  // measure time taken to read & write to ring of pipes and context
  // switch between processes
  if (pid < 0) {
    fprintf(stderr, "unable to fork\n");
    exit(1);
  } else if (pid == 0) {
    for (i = 0; i < ITERATIONS; i++) {
      read(pipefd2[0], buf, strlen(txt));
      write(pipefd3[1], txt, strlen(txt));
    }
  } else {
    clock_gettime(0, &tp2);

    for (i = 0; i < ITERATIONS; i++) {
      write(pipefd2[1], txt, strlen(txt));
      read(pipefd3[0], buf, strlen(txt));
    }

    clock_gettime(0, &tp3);

    long t_total =
        (tp3.tv_sec - tp2.tv_sec) * 1000000000 + tp3.tv_nsec - tp2.tv_nsec;
    long p_ring_rw_t_total =
        (tp1.tv_sec - tp0.tv_sec) * 1000000000 + tp1.tv_nsec - tp0.tv_nsec;
    long ctsw_t_total = t_total - p_ring_rw_t_total;

    printf("total time taken for context switching was %ldns\n", ctsw_t_total);
    printf("avg time taken for a context switch was %fns\n",
           (double)ctsw_t_total / NO_CTXSW);
  }

  return 0;
}
