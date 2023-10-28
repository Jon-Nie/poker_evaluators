#include <stdio.h>
#include <assert.h>
#include "../include/lib.h"

int main()
{
    uint64_t* deck_list = init_deck();
    uint64_t deck;
    for (int i = 0; i < 52; i++) {
        print_cards(deck_list[i]);
        deck = deck | deck_list[i];
    }

    printf("All cards: ");
    print_cards(deck);

    printf("All tests successful.\n");
}