#include <stdio.h>
#include "../include/utils.h"
#include "../include/lookup.h"

void load_lookup_tables()
{
    FILE* file;

    file = fopen("../tables/flushes5.data", "rb");
    fread(flushes5, sizeof(int), ARRSIZE_13_5, file);
    fclose(file);

    file = fopen("../tables/nonflushes5.data", "rb");
    fread(nonflushes5, sizeof(int), ARRSIZE_13_5, file);
    fclose(file);
}