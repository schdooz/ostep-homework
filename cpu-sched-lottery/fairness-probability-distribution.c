#include <stdlib.h>
#include <stdio.h>
#include <math.h>

long double factorial(int n) {
  if (n < 0) {
    fprintf(stderr, "attempted to compute negative factorial\n");
    exit(1);
  }

  if (n == 0) {
    return 1;
  }

  return (long double) n * factorial(n - 1);
}

int main() {
  int i;
  long double p;
  float expectation = 0;

  for (i = 1; i < 101; i++) {
    p = pow(0.5, 199 - i) * factorial(199 - i) / (factorial(100 - i) * factorial(99));
    expectation += (float) p * i;
    printf("P(X = %3d) = %10.3LE\n", i, p);
  }

  printf("E(X) = %.3f\n", expectation);

  exit(0);
}

