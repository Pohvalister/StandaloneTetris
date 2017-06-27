#include "types.h"
#include "colors.h"

#define MAX_COL 80//Max num of colums
#define MAX_ROW 25 //Max num of rows
#define OFF_COL 0//colums offset
#define OFF_ROW 0//rows offset
#define DEFAULT_COLOR WHITE

#define DEF_VRAM_BASE 0xb8000 //Default base for video memory

#define PUT_ON_SCREEN(symbol, curr_row, curr_col, color) ( ((unsigned short *) (DEF_VRAM_BASE)) \
[((OFF_ROW + curr_row)*MAX_COL) + curr_col+OFF_COL] = (color <<8)|(symbol))

//deprecated??
void print_data(char symbol_table[15][80], color_t color_table[15][80],size_t row_count,size_t col_count){//первый [] -col второй [] -row
    for (size_t i=0;i<row_count;i++){
        for (size_t j=0;j<col_count;j++)
            PUT_ON_SCREEN(symbol_table[i][j],i,j,color_table[i][j]);
    }
}

void print_colored_symbols(char color_table[15][80],size_t row_count,size_t col_count){
    for (size_t i=0;i<row_count;i++){
        for (size_t j=0;j<col_count;j++){
            size_t value = color_table[i][j];
            if ((value - 'a') < 8){
                PUT_ON_SCREEN(' ',i,j,color_mas[value - 'a']);
            }else{
                PUT_ON_SCREEN((char)value,i,j,DEFAULT_COLOR);
            }
        }
    }
}
void print_monotonic_table(char table[15][80],size_t row_count,size_t col_count,color_t COLOR){
    for (size_t i=0;i<row_count;i++){
        for (size_t j=0;j<col_count;j++){
			PUT_ON_SCREEN((char)table[i][j],i,j,COLOR);
        }
    }
}
void clear_screen(){
    for (size_t i=0;i<MAX_COL;i++){
        for (size_t j=0;j<MAX_ROW;j++)	
            PUT_ON_SCREEN(' ',j,i,DEFAULT_COLOR);
    }
}
