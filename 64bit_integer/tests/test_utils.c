#include <stdio.h>
#include <assert.h>
#include "../include/utils.h"

int main()
{
    uint8_t *active_bits = build_active_bits_table();
    uint64_t **index_tables = build_subindex_tables();

    uint64_t number;
    uint16_t *no_ptr = (uint16_t*)(&number);
    uint32_t index = 0;
    uint32_t computed_index;

    //popular combinations
    assert(bincoeff(49, 6) == 13983816);
    assert(bincoeff(52, 7) == 133784560);
    assert(bincoeff(52, 3) == 22100);
    assert(bincoeff(45, 2) == 990);

    //edge cases
    assert(bincoeff(-1, -1) == 0);
    assert(bincoeff(-1, 1) == 0);
    assert(bincoeff(1, -1) == 0);

    assert(bincoeff(0, 0) == 1);
    assert(bincoeff(0, 1) == 0);
    assert(bincoeff(1, 0) == 1);
    assert(bincoeff(1, 2) == 0);

    assert(bincoeff(14, 5) == bincoeff(14, 9));

    //testing active bits
    assert(active_bits[16384] == 1);
    assert(active_bits[8448] == 2);
    assert(active_bits[1540] == 3);
    assert(active_bits[2089] == 4);
    assert(active_bits[50433] == 5);
    assert(active_bits[24920] == 6);
    assert(active_bits[5415] == 7);
    assert(active_bits[26396] == 8);

    //testing subindices with 3 bits activated
    assert(index_tables[0][800] == 118);

    assert(index_tables[1][800] == 2598);
    assert(index_tables[1][800+ARRSIZE_16] == 14885);
    assert(index_tables[1][800+ARRSIZE_16*2] == 65087);
    assert(index_tables[1][800+ARRSIZE_16*3] == 225590);
    assert(index_tables[1][800+ARRSIZE_16*4] == 635646);
    assert(index_tables[1][800+ARRSIZE_16*5] == 0); //there can be 7 active bits at most
    assert(index_tables[1][800+ARRSIZE_16*6] == 0); //there can be 7 active bits at most

    assert(index_tables[2][800] == 11478);
    assert(index_tables[2][800+ARRSIZE_16] == 111817);
    assert(index_tables[2][800+ARRSIZE_16*2] == 848559);
    assert(index_tables[2][800+ARRSIZE_16*3] == 5220442);
    assert(index_tables[2][800+ARRSIZE_16*4] == 26756218);
    assert(index_tables[2][800+ARRSIZE_16*5] == 0); //there can be 7 active bits at most
    assert(index_tables[2][800+ARRSIZE_16*6] == 0); //there can be 7 active bits at most

    assert(index_tables[3][800] == 30854);
    assert(index_tables[3][800+ARRSIZE_16] == 424109);
    assert(index_tables[3][800+ARRSIZE_16*2] == 4577823);
    assert(index_tables[3][800+ARRSIZE_16*3] == 40400894);
    assert(index_tables[3][800+ARRSIZE_16*4] == 299723958);
    assert(index_tables[3][800+ARRSIZE_16*5] == 0); //there can be 7 active bits at most
    assert(index_tables[3][800+ARRSIZE_16*6] == 0); //there can be 7 active bits at most

    assert((index_tables[3][15+ARRSIZE_16*3] + index_tables[2][57344]-1) == bincoeff(52, 7)); //maximum index of c(52, 7)

    //testing that every computed index is correct
    for (size_t b1 = 6; b1 < 52; b1++) {
        for (size_t b2 = 5; b2 < b1; b2++) {
            for (size_t b3 = 4; b3 < b2; b3++) {
                for (size_t b4 = 3; b4 < b3; b4++) {
                    for (size_t b5 = 2; b5 < b4; b5++) {
                        for (size_t b6 = 1; b6 < b5; b6++) {
                            for (size_t b7 = 0; b7 < b6; b7++) {
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