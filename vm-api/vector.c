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
    if (index >= v->count) {
        return -1;
    }

    *val = v->buf[index];

    return 0;
}

int vector_mod(struct vector *v, unsigned long index, unsigned char val) {
    if (index >= v->count) {
        return -1;
    }

    v->buf[index] = val;

    return 0;
}

int main() {
    struct vector v = vector_ctor();
    unsigned char c;

    vector_add(&v, '0');
    vector_add(&v, '1');
    vector_add(&v, '2');
    vector_add(&v, '3');
    vector_add(&v, '4');
    vector_add(&v, '5');
    vector_add(&v, '6');
    vector_add(&v, '7');

    vector_get(&v, 0, &c);
    printf("First element is %c\n", c);

    vector_get(&v, 1, &c);
    printf("Second element is %c\n", c);

    printf("count is %lu\n", v.count);
    printf("buflen is %lu\n", v.buflen);

    vector_pop(&v, &c);
    printf("Popped value is %c\n", c);
    printf("count after popping is %lu\n", v.count);

    printf("Popping 4 more times...\n");
    vector_pop(&v, &c);
    vector_pop(&v, &c);
    vector_pop(&v, &c);
    vector_pop(&v, &c);

    printf("Last popped value is %c\n", c);
    printf("count is %lu\n", v.count);
    printf("buflen is %lu\n", v.buflen);
}