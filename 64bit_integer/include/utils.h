#include <stdint.h>

#ifndef LIB_DECLARATIONS
    #define LIB_DECLARATIONS

    #define ARRSIZE_16  65536

#endif

uint16_t *build_active_bits_table();
uint64_t bincoeff(uint16_t n, uint16_t k);
uint64_t **build_subindex_tables();