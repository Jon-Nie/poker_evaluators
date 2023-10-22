#include <stdio.h>
#include "../include/lib.h"
#include "../include/lookup.h"
#include <math.h>
#include <stdlib.h>

int build_7_hand_lookup_tables(Card deck[]);
int find_best_5hand_rank(Card cards[]);
void insert_7hand_rank(int rank, Card cards[]);

int main()
{
    Card* deck = init_deck(deck);
    load_lookup_tables();
    
    print_cards(deck, 52);
    printf("Rank: %d\n", flushes5[ACE + KING*13 + QUEEN*13*13 + JACK*13*13*13 + NINE*13*13*13*13]);
    int x = build_7_hand_lookup_tables(deck);
    printf("Total Ranks: %d\n", x);

    int success = 0;
    FILE* file;

    file = fopen("tables/nonflushes7.data", "wb");
    success = fwrite(nonflushes7, sizeof(int), ARRSIZE_13_7, file);
    fclose(file);
    if (success == 0) {
        printf("Error: couldn't write to nonflushes7 file.");
        return 1;
    }

    file = fopen("tables/flushes6.data", "wb");
    success = fwrite(flushes6, sizeof(int), ARRSIZE_13_6, file);
    fclose(file);
    if (success == 0) {
        printf("Error: couldn't write to flushes6 file.");
        return 2;
    }

    file = fopen("tables/flushes7.data", "wb");
    success = fwrite(flushes7, sizeof(int), ARRSIZE_13_7, file);
    fclose(file);
    if (success == 0) {
        printf("Error: couldn't write to flushes7 file.");
        return 3;
    }

}

int build_7_hand_lookup_tables(Card deck[])
{
    Card cards[7];
    int x = 0;
    int total = 133784560;
    float percentage = 0.0;

    for (int c1 = 0; c1 < 46; c1++) {
        printf("%d\n", c1);
        cards[0] = deck[c1];
        for (int c2 = c1+1; c2 < 47; c2++) {
            printf("\t%d\n", c2);
            cards[1] = deck[c2];
            for (int c3 = c2+1; c3 < 48; c3++) {
                printf("\t\t%d\n", c3);
                cards[2] = deck[c3];
                for (int c4 = c3+1; c4 < 49; c4++) {
                    printf("\t\t\t%d\n", c4);
                    cards[3] = deck[c4];
                    for (int c5 = c4+1; c5 < 50; c5++) {
                        cards[4] = deck[c5];
                        for (int c6 = c5+1; c6 < 51; c6++) {
                            cards[5] = deck[c6];
                            for (int c7 = c6+1; c7 < 52; c7++) {
                                cards[6] = deck[c7];
                                int rank = find_best_5hand_rank(cards);
                                insert_7hand_rank(rank, cards);
                                x++;
                                if ((int)(percentage*total) == x) {
                                    printf("Percentage: %f.2", percentage);
                                    percentage += 0.01;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return x;
}

int find_best_5hand_rank(Card cards[])
{
    int best = 7463;
    Card subhand[5];
    int rank;

    for (int row = 0; row < 21; row++) {
        for (int col = 0; col < 5; col++) {
            subhand[col] = cards[perm_7_5[row][col]];
        }
        rank = get_5hand_rank(subhand);
        if (rank < best) best = rank;
    }
    return best;
}

void insert_7hand_rank(int rank, Card cards[])
{
    unsigned int c1 = cards[0].value;
    unsigned int c2 = cards[1].value;
    unsigned int c3 = cards[2].value;
    unsigned int c4 = cards[3].value;
    unsigned int c5 = cards[4].value;
    unsigned int c6 = cards[5].value;
    unsigned int c7 = cards[6].value;

    int no_cards = 0;
    char suit;
    int* arr;
    int* card_values = malloc(sizeof(int) * 7);

    if ((suit = check_flush(cards, 7)) == -1) {
        no_cards = 7;
        arr = nonflushes7;
        for (int i = 0; i < 7; i++) {
            card_values[i] = cards[i].value;
        }
    } else {
        for (int i = 0; i < 7; i++) {
            if (cards[i].suit == suit) {
                no_cards++;
            }
        }

        if (no_cards == 5) {
            arr = flushes5;
        } else if (no_cards == 6) {
            arr = flushes6;
        } else {
            arr = flushes7;
        }

        int index = 0;
        for (int i = 0; i < 7; i++) {
            if (cards[i].suit == suit) {
                card_values[index++] = cards[i].value;
            }
        }
    }

    int no_permutations = permutations(no_cards);
    int **perm_array = permutations_array(card_values, no_cards);
    for (int col = 0; col < no_permutations; col++) {
        c1 = perm_array[col][0];
        c2 = perm_array[col][1];
        c3 = perm_array[col][2];
        c4 = perm_array[col][3];
        c5 = perm_array[col][4];
        if (no_cards == 5) {
            arr[c1 + (c2*13) + (c3*13*13) + (c4*13*13*13) + (c5*13*13*13*13)] = rank;
        } else if (no_cards == 6) {
            c6 = perm_array[col][5];
            arr[c1 + (c2*13) + (c3*13*13) + (c4*13*13*13) + (c5*13*13*13*13) + (c6*13*13*13*13*13)] = rank;
        } else {
            c6 = perm_array[col][5];;
            c7 = perm_array[col][6];;
            arr[c1 + (c2*13) + (c3*13*13) + (c4*13*13*13) + (c5*13*13*13*13) + (c6*13*13*13*13*13) + (c7*13*13*13*13*13*13)] = rank;
        }
    }

    for (int i = 0; i < no_permutations; i++) {
        free(perm_array[i]);
    }
    free(perm_array);
    free(card_values);
}