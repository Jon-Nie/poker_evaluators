#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/utils.h"

uint8_t *build_active_bits_table()
{
    uint8_t no_bits;
    uint8_t number;
    uint8_t *active_bits = malloc(sizeof(uint8_t) * ARRSIZE_16);

    for (int index = 0; index < ARRSIZE_16; index++) {
        number = index;
        no_bits = 0;
        while (number != 0) {
            no_bits += (number & 1);
            number >>= 1;
        }
        active_bits[index] = no_bits;
    }

    return active_bits;
}

uint64_t bincoeff(uint16_t n, uint16_t k)
{
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;

    return bincoeff(n-1, k-1) + bincoeff(n-1, k);
}