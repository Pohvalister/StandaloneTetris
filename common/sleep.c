#include "sleep.h"
#include "os_life.h"

extern uint64_t lifetime;

void sleep(uint64_t delta) {
	uint64_t cur_time = lifetime;
	uint64_t wakeup_time = cur_time + delta;
	while (lifetime < wakeup_time) {
		asm("hlt");
	}
}

extern my_status lifestatus; 

void sleep_until_waked_up() {
	lifestatus = SLEEPING;
	while(lifestatus == SLEEPING) {
		asm("hlt");
	}
}
