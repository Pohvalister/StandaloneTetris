#include "os_life.h"

my_state lifestatus = WORKING;
unsigned long long lifetime = 0;

unsigned int prev_random = 0;

const int RAND_MOD = 157;

int get_random_number(int modulus) {
	prev_random += lifetime;
	prev_random %= RAND_MOD;
	return prev_random % modulus;
}
