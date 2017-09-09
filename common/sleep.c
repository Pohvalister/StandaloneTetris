#include "sleep.h"
#include "os_life.h"

extern unsigned long long lifetime;

void sleep(unsigned long long secs) {
	unsigned long long t1 = lifetime;
	unsigned long long t2 = t1 + secs;
	while (lifetime < t2) {
		asm ("hlt");
	}
}

extern my_state lifestatus;

void sleep_until_awakaned() {
	lifestatus = SLEEPING;
	while (lifestatus == SLEEPING) {
		asm ("hlt");
	}
}
