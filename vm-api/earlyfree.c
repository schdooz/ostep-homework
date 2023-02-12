#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(sizeof(int) * 100);

    free(ptr);

    printf("My int is %d\n", ptr[49]);
}
