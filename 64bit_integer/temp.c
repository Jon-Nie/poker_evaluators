#include <stdio.h>
#include <stdint.h>

unsigned long long bincoeff(unsigned int n, unsigned int k)
{
    if ((k > n) || (k == 0)) return 0;

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

int main()
{
    uint16_t number = (1 << 15) | (1 << 2);
    uint16_t* number_ptr = &number;
    uint8_t* smaller_ptr = (uint8_t*)number_ptr;

    printf(   "%llu", (bincoeff(52,3)));
    /*
    printf("The number: %u\n", number);
    printf("The address of the number: %llu\n", number_ptr);
    printf("The pointer address: %llu\n", &number_ptr);
    printf("The pointer address of the smaller pointer: %llu\n", &smaller_ptr);
    printf("The address the smaller pointer points to: %llu\n", smaller_ptr);
    printf("The address the smaller pointer points to to the second byte: %llu\n", smaller_ptr+1);
    printf("The value of the pointer: %llu\n", *number_ptr);
    printf("The value of the smaller pointer: %llu\n", *smaller_ptr);
    printf("The next value of the smaller pointer: %llu\n", *(smaller_ptr+1));
    */
}