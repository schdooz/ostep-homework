#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(100);
    int *p = ptr + 10;

    free(p);
}
