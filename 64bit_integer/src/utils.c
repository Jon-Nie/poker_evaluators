#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/utils.h"

#define MAX_BITS    7

uint8_t *build_active_bits_table()
{
    uint8_t no_bits;
    uint16_t number;
    uint8_t *active_bits = malloc(sizeof(uint8_t) * ARRSIZE_16);

    for (uint32_t index = 0; index < ARRSIZE_16; index++) {
        number = index;
        no_bits = 0;
        for (int bit = 0; bit < 16; bit++) {
            if ((number & (1<<bit))) {
                no_bits += 1;
            }
        }
        active_bits[index] = no_bits;
    }

    return active_bits;
}

uint64_t bincoeff(uint16_t n, uint16_t k)
{
    if (k > n) return 0;

    uint64_t combis = 1;
    int stop;

    if (k > (n - k)) {
        stop = k;
        k = n - k;
    } else {
        stop = n - k;
    }

    // numerator
    while (n > stop) {
        combis *= n--;
    }

    // demoninator
    while (k >= 1) {
        combis /= k--;
    }

    return combis;
}