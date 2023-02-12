#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(sizeof(int) * 100);
    int *p = ptr + 10;

    free(p);
}
