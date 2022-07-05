#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(100);

    free(ptr);

    printf("My int is %d\n", ptr[49]);
}
