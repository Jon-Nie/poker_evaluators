#include <stdio.h>
#include "include/lib.h"
#include <time.h>
#include <stdlib.h>

int main()
{
    unsigned short* lookup = malloc(sizeof(unsigned short) * 133784560);
    for (int i = 0; i < 133784560; i++) {
        lookup[i] = 10;
    }
    unsigned long long* deck = init_deck();
    unsigned long long cards;
    unsigned int x = 0;
    unsigned int index;

    clock_t begin = clock();

    for (int c1 = 0; c1 < 46; c1++) {
        for (int c2 = c1+1; c2 < 47; c2++) {
            for (int c3 = c2+1; c3 < 48; c3++) {
                for (int c4 = c3+1; c4 < 49; c4++) {
                    for (int c5 = c4+1; c5 < 50; c5++) {
                        for (int c6 = c5+1; c6 < 51; c6++) {
                            for (int c7 = c6+1; c7 < 52; c7++) {
                                cards = deck[c1] | deck[c2] | deck[c3] | deck[c4] | deck[c5] | deck[c6] | deck[c7];
                                print_cards(cards);
                                index = 0;
                                index += index[cards & 0x1FFF];
                                index += index[cards & 0x3FFE000] * irgendwas;
                                index += index[cards & 0x7FFC000000] * irgendwas;
                                index += index[cards & 0xFFF8000000000] * irgendwas;
                                lookup[index];
                                x++;
                            }
                        }
                    }
                }
            }
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Ranks: %lu\nSeconds: %f\nLookups per Second: %d", x, time_spent, (int)(x/time_spent));
}