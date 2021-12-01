#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long double factorial(int n) {
  if (n < 0) {
    fprintf(stderr, "attempted to compute negative factorial\n");
    exit(1);
  }

  if (n == 0) {
    return 1;
  }

  return (long double)n * factorial(n - 1);
}

int main() {
  int i;
  long double p;
  float expectation = 0;

  printf("quanta q = 1\n");

  for (i = 1; i < 101; i++) {
    p = pow(0.5, 199 - i) * factorial(199 - i) /
        (factorial(100 - i) * factorial(99));
    expectation += (float)p * i;
    printf("P(X = %3d) = %10.3LE\n", i, p);
  }

  printf("E(X) = %.3f\n", expectation);

  expectation = 0;

  printf("quanta q = 2\n");

  for (i = 1; i < 51; i++) {
    p = pow(0.5, 99 - i) * factorial(99 - i) /
        (factorial(50 - i) * factorial(49));
    expectation += (float)p * 2 * i;
    printf("P(X = %3d) = %10.3LE\n", 2 * i, p);
  }

  printf("E(X) = %.3f\n", expectation);

  exit(0);
}
