#include <stdlib.h>

int** permutations_array(int elements[], int no_elements);
unsigned long long bincoeff(unsigned int n, unsigned int k);
unsigned long long permutations(unsigned int no_elements);
static void swap_elements(int* element1, int* element2);
static void fill_permutations(int elements[], int no_elements, int** array_pointer, int* row_idx_ptr, int start, int end);

int perm_7_5[21][5] =
{
    {0, 1, 2, 3, 4},
    {0, 1, 2, 3, 5},
    {0, 1, 2, 3, 6},
    {0, 1, 2, 4, 5},
    {0, 1, 2, 4, 6},
    {0, 1, 2, 5, 6},
    {0, 1, 3, 4, 5},
    {0, 1, 3, 4, 6},
    {0, 1, 3, 5, 6},
    {0, 1, 4, 5, 6},
    {0, 2, 3, 4, 5},
    {0, 2, 3, 4, 6},
    {0, 2, 3, 5, 6},
    {0, 2, 4, 5, 6},
    {0, 3, 4, 5, 6},
    {1, 2, 3, 4, 5},
    {1, 2, 3, 4, 6},
    {1, 2, 3, 5, 6},
    {1, 2, 4, 5, 6},
    {1, 3, 4, 5, 6},
    {2, 3, 4, 5, 6}
};


int** permutations_array(int elements[], int no_elements)
{
    int** array_ptr;
    int column_index = 0;

    int rows = permutations(no_elements);
    int** permutation_array = malloc(sizeof(int[rows][no_elements]));

    for (int i = 0; i < rows; i++) {
        permutation_array[i] = malloc(no_elements * sizeof(int));
    }

    array_ptr = permutation_array;
    fill_permutations(elements, no_elements, array_ptr, &column_index, 0, no_elements-1);

    return array_ptr;
}

unsigned long long bincoeff(unsigned int n, unsigned int k)
{
    if (k > n) return 0;

    unsigned long long combis = 1;
    int stop;

    if (k > (n - k)) {
        stop = k;
        k = n - k;
    } else {
        stop = n - k;
    }

    // numerator
    while (n > stop) {
        combis *= n--;
    }

    // demoninator
    while (k >= 1) {
        combis /= k--;
    }

    return combis;
}

unsigned long long permutations(unsigned int elements)
{
    int perms = 1;

    while (elements > 1) {
        perms *= elements--;
    }

    return perms;
}

static void swap_elements(int* n, int* m)
{
    int temp = *n;
    *n = *m;
    *m = temp;
}

static void fill_permutations(int elements[], int no_elements, int** array_pointer, int* row_idx_ptr, int start, int end)
{
    if (start == end) {
        for (int i = 0; i < no_elements; i++) {
            *(array_pointer[*row_idx_ptr]+i) = elements[i];
        }
        *row_idx_ptr += 1;
        return;
    }

    for (int i = start; i <= end; i++) {
        swap_elements(elements+i, elements+start);
        fill_permutations(elements, no_elements, array_pointer, row_idx_ptr, start+1, end);
        swap_elements(elements+i, elements+start);
    }
}