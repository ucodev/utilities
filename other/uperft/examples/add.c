#include <stdio.h>
#include <stdlib.h>

/* The name of the module (Shall be unique) */
const char perft_name[32] = "ADD Unit";

/* This function shall load all necessary data required by perft_run(). */
void *perft_load(void) {
	int *c = NULL;

	if (!(c = malloc(sizeof(int))))
		return NULL;

	*c = 3827136;

	return c;
}

/* Free any memory allocated by perft_load() */
void perft_unload(void *arg) {
	free(arg);
}

/* This is the unit test. The 'arg' parameter is provided by the return value of perft_load() */
int perft_run(void *arg) {
	volatile int *c = arg;
	volatile int a = 0, b = 123456;

	a += b + *c;

	return -!(a == 3950592);
}

