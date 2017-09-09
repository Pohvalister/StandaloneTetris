#include "tetris.h"
#include "sleep.h"

void main(void){
    while(1) {
        play_tetris();
        sleep_until_awakaned();
    }
}
