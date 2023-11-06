#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define DECK_SIZE 52

char *deck_char[DECK_SIZE] = {
    "Ac", "Ad", "Ah", "As",
    "Kc", "Kd", "Kh", "Ks",
    "Qc", "Qd", "Qh", "Qs",
    "Jc", "Jd", "Jh", "Js",
    "Tc", "Td", "Th", "Ts",
    "9c", "9d", "9h", "9s",
    "8c", "8d", "8h", "8s",
    "7c", "7d", "7h", "7s",
    "6c", "6d", "6h", "6s",
    "5c", "5d", "5h", "5s",
    "4c", "4d", "4h", "4s",
    "3c", "3d", "3h", "3s",
    "2c", "2d", "2h", "2s"
};

uint64_t *init_deck()
{
    uint64_t *deck = malloc(sizeof(uint64_t) * DECK_SIZE);

    for (size_t i = 0; i < DECK_SIZE; i++) {
        deck[i] = ((uint64_t)1 << i);
    }

    return deck;
}

void print_cards(uint64_t cards)
{
    for (size_t i = 0; i < DECK_SIZE; i++) {
        if (cards & 1) {
            printf("%s ", deck_char[i]);
        }
        cards >>= 1;
    }
    printf("\n");
}