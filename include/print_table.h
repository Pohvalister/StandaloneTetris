#ifndef PRINT_TABLE_H
#define PRINT_TABLE_H

#include "types.h"

void clear_screen(void);
void print_colored_symbols(char color_table[15][80],size_t row_count,size_t col_count);

#endif //PRINT_TABLE_H
