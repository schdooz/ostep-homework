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
  float sum = 0;

  for (i = 1; i < 101; i++) {
    p = pow(0.5, 199 - i) * factorial(199 - i) / (factorial(100 - i) * factorial(99));
    sum += (float) p;
    printf("P(X = %d) = %.20Lf\n", i, p);
  }

  printf("sum is %.20f\n", sum);

  exit(0);
}

