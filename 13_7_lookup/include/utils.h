#ifndef SYMBOLIC_DEFINITIONS
    #define SYMBOLIC_DEFINITIONS

    #define ARRSIZE_13_5 371293
    #define ARRSIZE_13_7 62748517
endif

/*
permutations_array returns a pointer to a two-dimensional array, with each sub-array/row representing one permutation without considering the order.
Example: permutations_array({5, 6, 7}, 3) returns a pointer to the following array:
{
    {5, 6, 7},
    {5, 7, 6},
    {6, 5, 7},
    {6, 7, 5},
    {7, 5, 6},
    {7, 6, 5}
}
*/
int** permutations_array(int elements[], int no_elements);

/*
bincoeff returns the binomial coefficient n over k. If k is greater than n, it returns 0.
Example: bincoeff(52, 3) returns 22.100, the total number of distinct possible Texas-Holdem flops without considering the order of drawing.
*/
unsigned long long bincoeff(unsigned int n, unsigned int k);

/*
permutations returns the factorial of a positive integer, which is the number of permutations of a set of n elements.
Example: There are 720 possibilities to draw 6 elements without replacement and with considering the order of drawing.
*/
unsigned long long permutations(unsigned int no_elements);

/*
perm_7_5 is an array of bincoeff(7, 5) = 21 arrays of possible index combinations of
drawing 5 indices of a 7-size array without replacement and without considering the order:
{
    {0, 1, 2, 3, 4},
    {0, 1, 2, 3, 5},
    ...
    {2, 3, 4, 5, 6}
}
*/
int perm_7_5[21][5];