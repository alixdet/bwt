#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rotations.h"

#define MAX_INPUT_SIZE ((size_t)(100 * BUFSIZ))

struct interval { size_t lo; size_t hi; };

struct interval bsearchinterval(
    const size_t ranks[],
    size_t size,
    struct rotation r,
    size_t charindex
) {
    assert(size > 0);

    struct interval result = { 0, size };

    const char target = charat(r, charindex);

    size_t m = 0;

    /* search for any location in interval  */
    for (;;) {
        assert(result.hi >= result.lo);

        m = (result.lo + result.hi) / 2;
        const char c = charat(nthrotation(r, ranks[m]), charindex);

        if (result.lo == result.hi) return result; /* not found */

        if (target == c) break;
        if (target < c) result.hi = m;
        if (target > c) result.lo = m + 1;
    }

    /* local bounds */
    size_t llo;
    size_t lhi;

    /* looking for lower bound */
    llo = result.lo;
    lhi = m;

    while (llo != lhi) {
        const char current = charat(nthrotation(r, ranks[result.lo]), charindex); 
        if (current == target) lhi = result.lo;
        else llo = result.lo + 1;

        result.lo = (llo + lhi) / 2; 
    }

    /* looking for upper bound */
    llo = m;
    lhi = result.hi;

    while (llo != lhi) {
        const char current = charat(nthrotation(r, ranks[lhi - 1]), charindex);
        if (current == target) llo = lhi;
        else lhi = result.hi;

        result.hi = (llo + lhi + 1) / 2; 
    }

    return result;
}

void insert(size_t * dest, size_t destsize, struct rotation rot) {
    size_t * remaining = dest;
    size_t remsize = destsize;

    size_t i = 0;

    while (i < rot.len && remsize > 0) {
        const struct interval interval = bsearchinterval(remaining, remsize, rot, i++);
        
        remaining = &remaining[interval.lo];
        remsize = interval.hi - interval.lo;
    }

    const size_t size = destsize - (remaining - dest);
    memmove(remaining + 1, remaining, size * sizeof(size_t));
    remaining[0] = rot.index;
}

int main(void) {
    /* static arrays required to avoid overflowing the stack. Memory
     * footprint and usage could be heavily optimized with dynamic
     * allocations.
     */
    static char input[MAX_INPUT_SIZE];
    static size_t ranks[MAX_INPUT_SIZE];

    size_t inputlen = 0;
    size_t rankslen = 0;

    /* required for reading safety and efficiency */
    assert(MAX_INPUT_SIZE % BUFSIZ == 0);

    for (;;) {
        char buffer[BUFSIZ];
        const size_t n = fread(buffer, sizeof(char), BUFSIZ, stdin);

        if (inputlen + n > MAX_INPUT_SIZE) {
            fprintf(
                stderr,
                "error: too much input (%zuB), max is %zuB",
                inputlen + n, MAX_INPUT_SIZE
            );
            abort();
        }
        memcpy(&input[inputlen], buffer, n);

        inputlen += n;
        if (n < BUFSIZ) break; /* EOF */
    }

    const struct rotation baserot = baserotation(input);

    for (size_t i = 0; i < inputlen; i++) {
        const struct rotation rot = nthrotation(baserot, i);
        insert(ranks, rankslen++, rot);

#ifdef DEBUG
        /* display the full table at every insertion step */
        for (size_t rank = 0; rank < rankslen; rank++) {
            const size_t index = ranks[rank];
            const struct rotation r = nthrotation(baserot, index);

            putchar('\t');

            for (size_t ci = 0; ci < baserot.len; ci++)
                putchar(charat(r, ci));
            putchar('\t');
            printf("%zu\n", index);
        }
        putchar('\n');
#endif
    }

    for (size_t i = 0; i < inputlen; i++) {
        const size_t index = ranks[i];
        const struct rotation r = nthrotation(baserot, index);
        putchar(charat(r, inputlen - 1)); /* print last column of BWT matrix */
    }

    return EXIT_SUCCESS;
}
