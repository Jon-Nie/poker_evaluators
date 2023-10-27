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

uint64_t bincoeff(int16_t n, int16_t k)
{
    if (k > n) return 0;
    if ((n < 0) || (k < 0)) return 0;

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

static uint64_t compute_subindex(uint16_t number, uint8_t bits_set, uint8_t additional_bits, uint8_t offset)
{
    uint64_t index = 1;

    for (int pos = 15; pos >= 0; pos--) {
        if ((number & (1 << pos)) && (bits_set != 0)) {
            index += bincoeff(pos+offset, bits_set+additional_bits);
            bits_set--;
        }
    }

    return index;
}

uint64_t **build_subindex_tables()
{
    uint64_t *lookup16 = malloc(sizeof(uint64_t) * ARRSIZE_16);
    uint64_t *lookup32 = malloc(sizeof(uint64_t) * ARRSIZE_16 * MAX_BITS);
    uint64_t *lookup48 = malloc(sizeof(uint64_t) * ARRSIZE_16 * MAX_BITS);
    uint64_t *lookup64 = malloc(sizeof(uint64_t) * ARRSIZE_16 * MAX_BITS);

    uint64_t **lookup_tables = malloc(sizeof(lookup16)*4);
    lookup_tables[0] = lookup16;
    lookup_tables[1] = lookup32;
    lookup_tables[2] = lookup48;
    lookup_tables[3] = lookup64;

    uint8_t *active_bits = build_active_bits_table();
    uint8_t bits_set, bits_left;
    uint64_t index16, index32, index48, index64;

    for (uint32_t number = 0; number < ARRSIZE_16; number++) {
        bits_set = active_bits[number];

        if (bits_set > 7) {
            continue;
        }
        bits_left = 7 - bits_set;

        index16 = compute_subindex(number, bits_set, 0, 0);
        lookup16[number] = index16;

        for (int additional_bits = 0; additional_bits <= bits_left; additional_bits++) {
            index32 = compute_subindex(number, bits_set, additional_bits, 16);
            lookup32[ARRSIZE_16*additional_bits + number] = index32;

            index48 = compute_subindex(number, bits_set, additional_bits, 32);
            lookup48[ARRSIZE_16*additional_bits + number] = index48;

            index64 = compute_subindex(number, bits_set, additional_bits, 48);
            lookup64[ARRSIZE_16*additional_bits + number] = index64;
        }
    }

    return lookup_tables;
}

uint32_t get_index(uint16_t *no_ptr, uint64_t **index_tables, uint8_t *bit_lookup)
{
    uint64_t *lookup16 = index_tables[0];
    uint64_t *lookup32 = index_tables[1];
    uint64_t *lookup48 = index_tables[2];
    uint64_t *lookup64 = index_tables[3];

    uint64_t no1 = *no_ptr++;
    uint64_t no2 = *no_ptr++;
    uint64_t no3 = *no_ptr++;
    uint64_t no4 = *no_ptr;

    uint8_t bits1 = bit_lookup[no1];
    uint8_t bits2 = bit_lookup[no2];
    uint8_t bits3 = bit_lookup[no3];
    uint8_t bits4 = bit_lookup[no4];

    uint64_t index1 = no1;
    uint64_t index2 = (bits1)*ARRSIZE_16 + no2;
    uint64_t index3 = (bits1+bits2)*ARRSIZE_16 + no3;
    uint64_t index4 = (bits1+bits2+bits3)*ARRSIZE_16 + no4;

    uint32_t index = lookup16[index1] + lookup32[index2] + lookup48[index3] + lookup64[index4] - 3;

    return index;
}