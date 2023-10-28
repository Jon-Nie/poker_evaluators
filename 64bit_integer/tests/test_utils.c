#include <stdio.h>
#include <assert.h>
#include "../include/utils.h"

int main()
{
    // popular combinations
    assert(bincoeff(49, 6) == 13983816);
    assert(bincoeff(52, 7) == 133784560);
    assert(bincoeff(52, 3) == 22100);
    assert(bincoeff(45, 2) == 990);

    // edge cases
    assert(bincoeff(-1, -1) == 0);
    assert(bincoeff(-1, 1) == 0);
    assert(bincoeff(1, -1) == 0);

    assert(bincoeff(0, 0) == 1);
    assert(bincoeff(0, 1) == 0);
    assert(bincoeff(1, 0) == 1);
    assert(bincoeff(1, 2) == 0);

    assert(bincoeff(14, 5) == bincoeff(14, 9));

    uint8_t *active_bits = build_active_bits_table();
    uint64_t **index_tables = build_subindex_tables();

    // testing active bits
    assert(active_bits[1] == 1);
    assert(active_bits[2] == 1);
    assert(active_bits[4] == 1);
    assert(active_bits[8] == 1);
    assert(active_bits[16] == 1);
    assert(active_bits[32] == 1);
    assert(active_bits[64] == 1);
    assert(active_bits[128] == 1);

    assert(active_bits[36] == 2);
    assert(active_bits[81] == 3);
    assert(active_bits[15] == 4);
    assert(active_bits[173] == 5);
    assert(active_bits[231] == 6);
    assert(active_bits[253] == 7);
    assert(active_bits[255] == 8);

    // testing subindices

    // testing that every computed index is correct
    uint64_t number;
    uint16_t *no_ptr = (uint16_t*)(&number);
    uint32_t index = 0;
    uint32_t computed_index;

    for (int b1 = 6; b1 < 52; b1++) {
        for (int b2 = 5; b2 < b1; b2++) {
            for (int b3 = 4; b3 < b2; b3++) {
                for (int b4 = 3; b4 < b3; b4++) {
                    for (int b5 = 2; b5 < b4; b5++) {
                        for (int b6 = 1; b6 < b5; b6++) {
                            for (int b7 = 0; b7 < b6; b7++) {
                                number = ((uint64_t)1 << b1) | ((uint64_t)1 << b2) | ((uint64_t)1 << b3) | ((uint64_t)1 << b4) | ((uint64_t)1 << b5) | ((uint64_t)1 << b6) | ((uint64_t)1 << b7);
                                index += 1;
                                computed_index = get_index(no_ptr, index_tables, active_bits);
                                assert(index == computed_index);
                            }
                        }
                    }
                }
            }
        }
    }

    printf("All tests successful.\n");
}