#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ARRSIZE_16  65536
#define MAX_BITS    7

uint8_t *build_active_bits_table()
{
    uint8_t no_bits;
    uint8_t number;
    uint8_t *active_bits = malloc(sizeof(short) * ARRSIZE_16);

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

uint64_t bincoeff(uint8_t n, uint8_t k)
{
    if ((k > n) || (k == 0)) return 0;

    uint32_t combis = 1;
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

uint32_t build_index_tables()
{
    uint32_t pattern, b1, b2, b3, b4, b5, b6, b7;

    uint32_t *lookup16 = malloc(sizeof(uint32_t) * ARRSIZE_16);
    uint32_t *lookup32 = malloc(sizeof(uint32_t) * ARRSIZE_16 * MAX_BITS);
    uint32_t *lookup48 = malloc(sizeof(uint32_t) * ARRSIZE_16 * MAX_BITS);
    uint32_t *lookup64 = malloc(sizeof(uint32_t) * ARRSIZE_16 * MAX_BITS);
    uint16_t position;
    uint8_t bits_set;
    uint8_t *active_bits = build_active_bits_table();

    for (int a = 6; a < 13; a++) {
        b1 = (1 << a);
        pattern = b1;
        bits_set = active_bits[pattern];
        position = get_index_position(pattern);
        lookup1[pattern] = position;
        for (int b = 0; b < a; b++) {
            b2 = (1 << b);
            pattern = b1 | b2;
            bits_set = active_bits[pattern];
            position = get_index_position(pattern);
            lookup1[pattern] = position;
            for (int c = 0; c < b; c++) {
                b3 = (1 << c);
                pattern = b1 | b2 | b3;
                bits_set = active_bits[pattern];
                position = get_index_position(pattern);
                for (int d = 0; d < c; d++) {
                    b4 = (1 << d);
                    pattern = b1 | b2 | b3 | b4;
                    bits_set = active_bits[pattern];
                    position = get_index_position(pattern);
                    for (int e = 0; e < d; e++) {
                        b5 = (1 << e);
                        pattern = b1 | b2 | b3 | b4 | b5;
                        bits_set = active_bits[pattern];
                        position = get_index_position(pattern);
                        for (int f = 0; f < e; f++) {
                            b6 = (1 << f);
                            pattern = b1 | b2 | b3 | b4 | b5 | b6;
                            bits_set = active_bits[pattern];
                            position = get_index_position(pattern);
                        }
                    }
                }
            }
        }
    }
}


uint32_t test_index_lookup()
{
    uint32_t pattern, b1, b2, b3, b4, b5, b6, b7;
    uint32_t index = 0;
    uint16_t pattern1, pattern2, pattern3, pattern4;

    for (int a = 6; a < 52; a++) {
        b1 = (1 << a);
        for (int b = 5; b < a; b++) {
            b2 = (1 << b);
            for (int c = 4; c < b; c++) {
                b3 = (1 << c);
                for (int d = 3; d < c; d++) {
                    b4 = (1 << d);
                    for (int e = 2; e < d; e++) {
                        b5 = (1 << e);
                        for (int f = 1; f < e; f++) {
                            b6 = (1 << f);
                            for (int g = 0; g < f; g++) {
                                b7 = (1 << g);
                                pattern = b1 | b2 | b3 | b4 | b5 | b6 | b7;
                                pattern1 = pattern & 0x1FFF;
                                pattern2 = (pattern & 0x3FFE000) >> 13;
                                pattern3 = (pattern & 0x7FFC000000) >> 26;
                                pattern4 = (pattern & 0xFFF8000000000) >> 39;
                            }
                        }
                    }
                }
            }
        }
    }
    return index;
}

uint32_t get_index_position(uint32_t bitpattern)
{
    int remaining_bits = 7;
    uint32_t index = 0;
    int leftmost = 51;
    
    while (remaining_bits) {
        for (int position = leftmost; position >= 0; position--) {
            if (bitpattern & (1 << position)) {
                index += bincoeff(position-1, remaining_bits);
                leftmost = position-1;
                remaining_bits--;
            }
        }
    }

    return index;
}


int main()
{
    uint32_t x = build_index_tables();
    printf("Indexes: %lu", x);
}


int lookup()
{
    uint16_t x = 0;
    uint32_t cards, a, b, c, d;

    short index_a[8192], index_b[8192], index_c[8192], index_d[8192];

    for (int b1 = 6; b1 < 52; b1++) {
        for (int b2 = 5; b2 < b1; b2++) {
            for (int b3 = 4; b3 < b2; b3++) {
                for (int b4 = 3; b4 < b3; b4++) {
                    for (int b5 = 2; b5 < b4; b5++) {
                        for (int b6 = 1; b6 < b5; b6++) {
                            for (int b7 = 0; b7 < b6; b7++) {
                                cards = (1 << b1) | (1 << b2) | (1 << b3) | (1 << b4) | (1 << b5) | (1 << b6) | (1 << b7);
                                a = cards & 0x1FFF;
                                b = cards & 0x3FFE000;
                                c = cards & 0x7FFC000000;
                                d = cards & 0xFFF8000000000;
                                
                                x++;
                            }
                        }
                    }
                }
            }
        }
    }

    return 1;
}