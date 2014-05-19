/**
 * @file unit.c
 * @brief uPerfT unit test interface.
 */

/*
   uPerfT - Performance Tester

   Copyright 2014 Pedro A. Hortas (pah@ucodev.org)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#include <stdio.h>
#include <time.h>

#include "stack.h"
#include "unit.h"
#include "cexit.h"

static unsigned long _loops = UNIT_ITERATIONS_DEFAULT;

void unit_set_loops(unsigned long loops) {
	if (!loops)
		cexit_failure("Loops must be greater than zero.");

	_loops = loops;
}

void unit_test(void) {
	clock_t clk_init = 0, clk_end = 0;
	struct stack_unit *e = NULL;

	while ((e = hll->pop(hll))) {
		printf("==== RUNNING UNIT TEST FOR \'%s\' (%lu iterations) ====\n", e->name, _loops);

		clk_init = clock();

		for (e->loops = 0; e->loops < _loops; e->loops ++) {
			if (e->run(e->arg) < 0)
				e->errors ++;
		}

		clk_end = clock();

		printf("==== UNIT TEST COMPLETED FOR \'%s\' ====\n", e->name);

		e->avg_time = (long double) (((clk_end - clk_init) / (long double) e->loops) / (long double) CLOCKS_PER_SEC) * (long double) 1000000;
		e->total_time = (long double) ((clk_end - clk_init) / (long double) CLOCKS_PER_SEC) * (long double) 1000;

		hlr->push(hlr, e);
	}
}

