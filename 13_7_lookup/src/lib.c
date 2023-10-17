#include <stdio.h>
#include "../include/lib.h"

char values[] = {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
char values_char[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
char suits[] = {CLUBS, DIAMONDS, HEARTS, SPADES};
char suits_char[] = {'c', 'd', 'h', 's'};

int get_5hand_rank(Card cards[], int flush_lookup[], int nonflush_lookup[])
{
    unsigned int c1 = cards[0].value;
    unsigned int c2 = cards[1].value;
    unsigned int c3 = cards[2].value;
    unsigned int c4 = cards[3].value;
    unsigned int c5 = cards[4].value;

    if(check_flush(cards, 5)) {
        return flush_lookup[c1 + (c2*13) + (c3*13*13) + (c4*13*13*13) + (c5*13*13*13*13)];
    } else {
        return nonflush_lookup[c1 + (c2*13) + (c3*13*13) + (c4*13*13*13) + (c5*13*13*13*13)];
    }
}

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