#include <stdbool.h>
#include <string.h>

/* TODO: remove */
#include <stdio.h>

#include "rotations.h"

struct rotation baserotation(const char * chars) {
    struct rotation result = { .string = chars, .len = strlen(chars), .index = 0 };
    return result;
}

struct rotation nthrotation(struct rotation r, size_t n) {
    struct rotation result = { .string = r.string, .len = r.len, .index = n };
    return result;
}

bool endrotation(struct rotation r) {
    return r.index >= r.len;
}

char charat(struct rotation rotation, size_t charindex) {
    const size_t len = rotation.len;
    const size_t i = (len - rotation.index + charindex) % len;
    return rotation.string[i];
}
