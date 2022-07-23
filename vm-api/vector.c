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

void vector_append(struct vector *v, unsigned char byte) {
    if (v->count + 1 > v->buflen) {
        v->bytes = realloc(v->bytes, (v->buflen)*2);
        v->buflen = (v->buflen)*2;
    }

    v->bytes[v->count] = byte;

    v->count++;
}

unsigned char vector_get(struct vector *v, unsigned long index) {
    return v->bytes[index];
}
