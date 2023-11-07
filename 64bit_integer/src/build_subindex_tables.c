#include <stdio.h>
#include "../include/utils.h"

int main()
{
    size_t success = 0;
    FILE *file;

    uint64_t **index_tables = build_subindex_tables();
    uint64_t *index16 = index_tables[0];
    uint64_t *index32 = index_tables[1];
    uint64_t *index48 = index_tables[2];
    uint64_t *index64 = index_tables[3];

    file = fopen("tables/index16.data", "wb");
    success = fwrite(index16, sizeof(uint64_t), ARRSIZE_16, file);
    fclose(file);
    if (success == 0) {
        printf("Error: couldn't write to index16 file.");
        return 1;
    }

    file = fopen("tables/index32.data", "wb");
    success = fwrite(index32, sizeof(uint64_t), ARRSIZE_16*7, file);
    fclose(file);
    if (success == 0) {
        printf("Error: couldn't write to index32 file.");
        return 1;
    }

    file = fopen("tables/index48.data", "wb");
    success = fwrite(index48, sizeof(uint64_t), ARRSIZE_16*7, file);
    fclose(file);
    if (success == 0) {
        printf("Error: couldn't write to index48 file.");
        return 1;
    }

    file = fopen("tables/index64.data", "wb");
    success = fwrite(index64, sizeof(uint64_t), ARRSIZE_16*7, file);
    fclose(file);
    if (success == 0) {
        printf("Error: couldn't write to index64 file.");
        return 1;
    }

    printf("All subindex tables successfully built.\n");
}