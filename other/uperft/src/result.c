/**
 * @file result.c
 * @brief uPerfT results interface.
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

#include "stack.h"
#include "export.h"

void result_dump(void) {
	struct stack_unit *e = NULL;

	puts("\n\n");

	while ((e = hlr->pop(hlr))) {
		printf("\n==== UNIT TEST RESULTS FOR \'%s\' ====\n\n", e->name);

		printf("\t+ Average time per iteration: %Lf usec(s).\n", e->avg_time);
		printf("\t+ Total execution time: %Lf msec(s).\n", e->total_time);
		printf("\t+ Total detected errors: %lu\n", e->errors);
		printf("\t+ Total iterations: %lu\n", e->loops);

		printf("\n==== END OF UNIT TEST RESULTS FOR \'%s\' ====\n\n", e->name);

		export_data(e);

		stack_unit_destroy(e);
	}
}

