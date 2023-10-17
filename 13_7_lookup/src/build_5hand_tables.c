#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"

int build_5hand_lookup_tables();
void insert_5hand_rank(int ranks[], int cards[], int rank);

enum VALUES {
    TWO = 0,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};

int flushes[13*13*13*13*13];
int nonflushes[13*13*13*13*13];

int main()
{
    int success = 0;
    FILE* file;

    int ranks = build_5hand_lookup_tables();
    if (ranks != 7462) {
        printf("Error: Couldn't build lookup table.");
        return 1;
    }

    file = fopen("tables/flushes5.data", "wb");
    success = fwrite(flushes, sizeof(int), 371293, file);
    fclose(file);

    if (success == 0) {
        printf("Error: couldn't write to flushes file.");
        return 2;
    }

    file = fopen("tables/nonflushes5.data", "wb");
    success = fwrite(nonflushes, sizeof(int), 371293, file);
    fclose(file);

    if (success == 0) {
        printf("Error: couldn't write to nonflushes file.");
        return 3;
    }

    return 0;
}

int build_5hand_lookup_tables()
{
    int temp = 0;
    int rank = 0;
    int cards[5];
    int wheel[5] = {ACE, TWO, THREE, FOUR, FIVE};

    printf("\nBuilding Table...\n");

    // Straight Flushes until 23456
    for (int i = ACE; i >= SIX; i--) {
        for (int n = 0; n < 5; n++) {
            cards[n] = i-n;
        }
        rank++;
        insert_5hand_rank(flushes, cards, rank);
    }

    // A2345 Straight Flush
    memcpy(cards, wheel, sizeof(cards));
    rank++;
    insert_5hand_rank(flushes, cards, rank);
    printf("Straight Flushes:\t%d\n", rank-temp);
    temp = rank;

    // Four of a Kinds
    for (int i = ACE; i >= TWO; i--) {
        for (int n = 0; n < 4; n++) {
            cards[n] = i;
        }
        for (int j = ACE; j >= TWO; j--) {
            if (i == j) continue;
            cards[4] = j;
            rank++;
            insert_5hand_rank(nonflushes, cards, rank);
        }
    }
    printf("Four of a Kinds:\t%d\n", rank-temp);
    temp = rank;

    // Full Houses
    for (int i = ACE; i >= TWO; i--) {
        for (int n = 0; n < 3; n++) {
            cards[n] = i;
        }
        for (int j = ACE; j >= TWO; j--) {
            if (i == j) continue;
            for (int n = 3; n < 5; n++) {
                cards[n] = j;
            }
            rank++;
            insert_5hand_rank(nonflushes, cards, rank);
        }
    }
    printf("Full Houses:\t\t%d\n", rank-temp);
    temp = rank;

    // Flushes
    for (int a = ACE; a >= SIX; a--) {
        cards[0] = a;
        for (int b = a-1; b >= FIVE; b--) {
            cards[1] = b;
            for (int c = b-1; c >= FOUR; c--) {
                cards[2] = c;
                for (int d = c-1; d >= THREE; d--) {
                    cards[3] = d;
                    for (int e = d-1; e >= TWO; e--) {
                        // ignore straight flushes
                        if (a == b+1 && a == c+2 && a == d+3 && a == e+4) continue;
                        // ignore A2345 straight flush
                        if (a == ACE && b == FIVE && c == FOUR && d == THREE && e == TWO) continue;
                        cards[4] = e;
                        rank++;
                        insert_5hand_rank(flushes, cards, rank);
                    }
                }
            }
        }
    }
    printf("Flushes:\t\t%d\n", rank-temp);
    temp = rank;
    
    // Straights until 23456
    for (int i = ACE; i >= SIX; i--) {
        for (int n = 0; n < 5; n++) {
            cards[n] = i-n;
        }
        rank++;
        insert_5hand_rank(nonflushes, cards, rank);
    }

    // A2345 Straight
    memcpy(cards, wheel, sizeof(cards));
    rank++;
    insert_5hand_rank(nonflushes, cards, rank);
    printf("Straights:\t\t%d\n", rank-temp);
    temp = rank;

    // Three of a Kinds
    for (int i = ACE; i >= TWO; i--) {
        for (int n = 0; n < 3; n++) {
            cards[n] = i;
        }
        for (int j = ACE; j >= TWO; j--) {
            if (i == j) continue;
            cards[3] = j;
            for (int k = j-1; k >= TWO; k--) {
                if (i == k || j == k) continue;
                cards[4] = k;
                rank++;
                insert_5hand_rank(nonflushes, cards, rank);
            }
        }
    }
    printf("Three of a Kinds:\t%d\n", rank-temp);
    temp = rank;

    // Two Pairs
    for (int i = ACE; i >= TWO; i--) {
        for (int n = 0; n < 2; n++) {
            cards[n] = i;
        }
        for (int j = i-1; j >= TWO; j--) {
            for (int n = 2; n < 4; n++) {
                cards[n] = j;
            }
            for (int k = ACE; k >= TWO; k--) {
                if (k == i || k == j) continue;
                cards[4] = k;
                rank++;
                insert_5hand_rank(nonflushes, cards, rank);
            }
        }
    }
    printf("Two Pairs:\t\t%d\n", rank-temp);
    temp = rank;

    // One Pairs
    for (int a = ACE; a >= TWO; a--) {
        cards[0] = a;
        cards[1] = a;
        for (int b = ACE; b >= TWO; b--) {
            if (b == a) continue;
            cards[2] = b;
            for (int c = b-1; c >= TWO; c--) {
                if (c == a || c == b) continue;
                cards[3] = c;
                for (int d = c-1; d >= TWO; d--) {
                    if (d == a || d == b || d == c) continue;
                    cards[4] = d;
                    rank++;
                    insert_5hand_rank(nonflushes, cards, rank);
                }
            }
        }
    }
    printf("One Pairs:\t\t%d\n", rank-temp);
    temp = rank;

    // High Cards
    for (int a = ACE; a >= SIX; a--) {
        cards[0] = a;
        for (int b = a-1; b >= FIVE; b--) {
            cards[1] = b;
            for (int c = b-1; c >= FOUR; c--) {
                cards[2] = c;
                for (int d = c-1; d >= THREE; d--) {
                    cards[3] = d;
                    for (int e = d-1; e >= TWO; e--) {
                        // ignore straight flushes
                        if (a == b+1 && a == c+2 && a == d+3 && a == e+4) continue;
                        // ignore A2345 straight flush
                        if (a == ACE && b == FIVE && c == FOUR && d == THREE && e == TWO) continue;
                        cards[4] = e;
                        rank++;
                        insert_5hand_rank(nonflushes, cards, rank);
                    }
                }
            }
        }
    }
    printf("High Cards:\t\t%d\n", rank-temp);
    printf("Total Ranks: %d", rank);

    return rank;
}

void insert_5hand_rank(int ranks[], int cards[], int rank)
{
    int c1;
    int c2;
    int c3;
    int c4;
    int c5;

    int no_permutations = permutations(5);
    int **perm_array = permutations_array(cards, 5);
    for (int col = 0; col < no_permutations; col++) {
        c1 = perm_array[col][0];
        c2 = perm_array[col][1];
        c3 = perm_array[col][2];
        c4 = perm_array[col][3];
        c5 = perm_array[col][4];
        ranks[c1 + (c2*13) + (c3*13*13) + (c4*13*13*13) + (c5*13*13*13*13)] = rank;
    }

    for (int i = 0; i < no_permutations; i++) {
        free(perm_array[i]);
    }
    free(perm_array);
}