#include <stdlib.h>

int main() {
    int *data = malloc(sizeof(int) * 100);

    data[100] = 0;

    free(data);
}
