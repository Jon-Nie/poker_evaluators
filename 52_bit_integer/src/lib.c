#include <stdio.h>
#include <stdlib.h>

char* deck_char[52] = {
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

unsigned long long* init_deck()
{
    unsigned long long* deck = malloc(sizeof(unsigned long long) * 52);
    unsigned long long card = 1;

    for (int i = 0; i < 52; i++) {
        deck[i] = card;
        card = card << 1;
    }

    return deck;
}

void print_cards(unsigned long long cards)
{
    for (int i = 0; i < 52; i++) {
        if (cards & 1) {
            printf("%s ", deck_char[i]);
        }
        cards >>= 1;
    }
    printf("\n");
}