#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void zero_arr(char *arr) {
    size_t len = strlen(arr);
    size_t i;

    for (i = 0; i < len; i++) {
        arr[i] = '0';
    }
}

int main(int argc, char *argv[]) {
    long bytes = -1;
    char *arr;

    if (argc == 1) {
        printf("Please specify amount of memory to use in MiB.\n");
        exit(1);
    } else if (argc > 2) {
        printf("Invalid number of arguments.\n");
        exit(1);
    }

    bytes = strtol(argv[1], NULL, 10);

    if (bytes < 0) {
        printf("Invalid number of MiB specified.\n");
        exit(1);
    }

    bytes *= 1048576;

    arr = malloc(bytes);

    while (1) {
        zero_arr(arr);
    }
}
