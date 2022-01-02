#ifndef rotationS_H
#define rotationS_H

#include <stdbool.h>
#include <stddef.h>

struct rotation {
    const char * string;
    size_t len;
    size_t index;
};

struct rotation;

struct rotation baserotation(const char * string);
struct rotation nthrotation(struct rotation, size_t n);

bool endrotation(struct rotation);

char charat(struct rotation rotation, size_t charindex);

#endif
