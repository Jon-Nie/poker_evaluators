#include <stdio.h>
#include "../include/lib.h"

char values[] = {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
char values_char[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
char suits[] = {CLUBS, DIAMONDS, HEARTS, SPADES};
char suits_char[] = {'c', 'd', 'h', 's'};

char check_flush(Card cards[], int no_elements)
{
    char suit;
    char suits[4] = {0};

    for (int i = 0; i < no_elements; i++) {
        suit = cards[i].suit;
        suits[suit]++;
        if (suits[suit] == 5) return suit;
    }

    return -1;
}

void print_cards(Card cards[], int no_elements)
{
    for (int i = 0; i < no_elements; i++) {
        printf("%c%c ", values_char[cards[i].value], suits_char[cards[i].suit]);
    }
    printf("\n");
}

void init_deck(Card deck[])
{
    int index = 0;

    for (int value = 0; value <= ACE; value++) {
        for (int suit = 0; suit <= SPADES; suit++) {
            Card card = {.value = value, .suit = suit};
            *deck[index++] = card;
        }
    }
}