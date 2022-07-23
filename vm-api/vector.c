#include <stdio.h>
#include <stdlib.h>

struct vector {
    unsigned char *bytes;
    unsigned long count;
    unsigned long buflen;
};

struct vector vector_ctor() {
    struct vector v;

    v.bytes = malloc(1);
    v.count = 0;
    v.buflen = 1;

    return v;
}

int vector_add(struct vector *v, unsigned char byte) {
    if (v->count + 1 > v->buflen) {
        v->bytes = realloc(v->bytes, (v->buflen)*2);

        if (v->bytes == NULL) {
            return -1;
        }

        v->buflen = (v->buflen)*2;
    }

    v->bytes[v->count] = byte;

    v->count++;

    return 0;
}

unsigned char vector_get(struct vector *v, unsigned long index) {
    return v->bytes[index];
}

int vector_mod(struct vector *v, unsigned long index, unsigned char val) {
    if (index >= v->count) {
        return -1;
    }

    v->bytes[index] = val;

    return 0;
}

int main() {
    struct vector v = vector_ctor();

    vector_add(&v, 'a');
    vector_add(&v, 'b');
    vector_add(&v, 'c');

    printf("First element is %c\n", vector_get(&v, 0));
    printf("Second element is %c\n", vector_get(&v, 1));
    printf("buflen is %lu\n", v.buflen);
}