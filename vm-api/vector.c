#include <stdio.h>
#include <stdlib.h>

#define MINBUFLEN 8

struct vector {
    unsigned char *buf;
    unsigned long count;
    unsigned long buflen;
};

struct vector vector_ctor() {
    struct vector v;

    v.buf = malloc(MINBUFLEN);
    v.count = 0;
    v.buflen = 1;

    return v;
}

void vector_destroy(struct vector *v) {
    free(v->buf);
    v->count = 0;
    v->buflen = 0;
}

int vector_add(struct vector *v, unsigned char byte) {
    unsigned char *new_buf;

    if (v->count + 1 > v->buflen) {
        new_buf = realloc(v->buf, (v->buflen)*2);

        if (new_buf == NULL) {
            return -1;
        }

        v->buf = new_buf;
        v->buflen = (v->buflen)*2;
    }

    v->buf[v->count] = byte;

    v->count++;

    return 0;
}

int vector_pop(struct vector *v, unsigned char *val) {
    unsigned char *new_buf;

    if (v->count <= 0) {
        return -1;
    }

    *val = v->buf[--(v->count)];

    if ((v-> buflen >= (2 * MINBUFLEN)) && (v->count < (v->buflen / 2))) {
        new_buf = realloc(v->buf, (v->buflen / 2));

        if (new_buf == NULL) {
            return -1;
        }

        v->buf = new_buf;
        v->buflen /= 2;
    }

    return 0;
}

int vector_get(struct vector *v, unsigned long index, unsigned char *val) {
    if (index >= v->count || index < 0) {
        return -1;
    }

    *val = v->buf[index];

    return 0;
}

int vector_mod(struct vector *v, unsigned long index, unsigned char val) {
    if (index >= v->count || index < 0) {
        return -1;
    }

    v->buf[index] = val;

    return 0;
}

int main() {
    struct vector v = vector_ctor();
    int i, len = 1025;
    unsigned char c;
    
    for (i = 0; i < len; i++) {
        vector_add(&v, i % 256);
    }

    vector_get(&v, 0, &c);
    printf("First element is %d\n", c);

    vector_get(&v, 1, &c);
    printf("Second element is %d\n", c);

    printf("count is %lu\n", v.count);
    printf("buflen is %lu\n", v.buflen);

    vector_pop(&v, &c);
    printf("Popped value is %d\n", c);
    printf("count after popping once is %lu\n", v.count);

    printf("Popping 513 more times...\n");

    for (i = 0; i < 513; i ++) {
        vector_pop(&v, &c);
    }

    printf("Last popped value is %d\n", c);
    printf("count is %lu\n", v.count);
    printf("buflen is %lu\n", v.buflen);

    vector_destroy(&v);
}