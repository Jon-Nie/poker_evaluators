#include <stdint.h>

#ifndef LIB_DECLARATIONS
    #define LIB_DECLARATIONS

    #define ARRSIZE_16  65536

#endif

uint8_t *build_active_bits_table();
uint64_t bincoeff(int16_t n, int16_t k);
uint64_t **build_subindex_tables();