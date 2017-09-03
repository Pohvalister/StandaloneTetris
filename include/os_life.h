#ifndef OS_LIFE_H
#define OS_LIFE_H

typedef enum {
	WORKING,
	SLEEPING,
} my_status;

static my_status lifestatus = SLEEPING;
static uint64_t lifetime = 0;

#endif //OS_LIFE_H
