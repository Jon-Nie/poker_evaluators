#include <stdio.h>
#include <stdlib.h>
#include "../include/lib.h"
#include "../include/lookup.h"

char values[] = {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
char values_char[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
char suits[] = {CLUBS, DIAMONDS, HEARTS, SPADES};
char suits_char[] = {'c', 'd', 'h', 's'};

int get_5hand_rank(Card cards[])
{
    unsigned int c1 = cards[0].value;
    unsigned int c2 = cards[1].value;
    unsigned int c3 = cards[2].value;
    unsigned int c4 = cards[3].value;
    unsigned int c5 = cards[4].value;

    if ((check_flush(cards, 5)) == -1) {
        return nonflushes5[c1 + (c2*13) + (c3*13*13) + (c4*13*13*13) + (c5*13*13*13*13)];
    } else {
        return flushes5[c1 + (c2*13) + (c3*13*13) + (c4*13*13*13) + (c5*13*13*13*13)];
    }
}

int get_7hand_rank(Card cards[])
{
    unsigned int c1 = cards[0].value;
    unsigned int c2 = cards[1].value;
    unsigned int c3 = cards[2].value;
    unsigned int c4 = cards[3].value;
    unsigned int c5 = cards[4].value;
    unsigned int c6 = cards[5].value;
    unsigned int c7 = cards[6].value;

    int no_cards = 0;
    int index = 0;
    char suit;

    if ((suit = check_flush(cards, 7)) == -1) {
        return nonflushes7[c1 + (c2*13) + (c3*13*13) + (c4*13*13*13) + (c5*13*13*13*13) + (c6*13*13*13*13*13) + (c7*13*13*13*13*13*13)];
    } else {
        for (int i = 0; i < 7; i++) {
            if (cards[i].suit == suit) {
                index += cards[i].value * (13 * no_cards);
                no_cards;
            }
        }

        if (no_cards == 5) {
            return flushes5[index];
        } else if (no_cards == 6) {
            return flushes6[index];
        } else {
            return flushes7[index];
        }
    }
}

char check_flush(Card cards[], int no_elements)
{
    char suit;
    char suit_counts[4] = {0};

    for (int i = 0; i < no_elements; i++) {
        suit = cards[i].suit;
        suit_counts[suit]++;
        if (suit_counts[suit] == 5) return suit;
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

Card* init_deck()
{
    int index = 0;
    Card* deck = malloc(sizeof(Card) * 52);

    for (int value = 0; value <= ACE; value++) {
        for (int suit = 0; suit <= SPADES; suit++) {
            Card card = {.value = value, .suit = suit};
            deck[index++] = card;
        }
    }

    return deck;
}