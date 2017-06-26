#ifndef NIDEDFUNC_PRINT_TABLE_H
#define NIDEDFUNC_PRINT_TABLE_H

#include "types.h"

void clear_screen(void);
void print_data(char symbol_table[15][80], color_t color_table[15][80],size_t row_count,size_t col_count);
void print_colored_symbols(char color_table[15][80],size_t row_count,size_t col_count);
void print_monotonic_table(char table[15][80],size_t row_count,size_t col_count,color_t COLOR);

#endif //NIDEDFUNC_PRINT_TABLE_H

