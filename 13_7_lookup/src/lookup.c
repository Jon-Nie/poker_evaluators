#include <stdio.h>
#include "../include/utils.h"
#include "../include/lookup.h"

void load_lookup_tables()
{
    FILE* file;

    file = fopen("tables/flushes5.data", "rb");
    int success = fread(flushes5, sizeof(int), ARRSIZE_13_5, file);
    fclose(file);
    if (success == 0) {
        printf("Error: couldnt read flushes5 file.\n");
    }

    file = fopen("tables/nonflushes5.data", "rb");
    fread(nonflushes5, sizeof(int), ARRSIZE_13_5, file);
    fclose(file);
    if (success == 0) {
        printf("Error: couldnt read nonflushes5 file.\n");
    }
}