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


    // testing that every computed index is correct
    uint64_t **index_tables = build_subindex_tables();
    uint8_t *bit_lookup = build_active_bits_table();

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
                                computed_index = get_index(no_ptr, index_tables, bit_lookup);
                                assert(index == computed_index);
                            }
                        }
                    }
                }
            }
        }
    }
}