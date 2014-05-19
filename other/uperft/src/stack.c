/**
 * @file stack.c
 * @brief uPerfT stack interface.
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
#include <string.h>
#include <errno.h>
#include <dlfcn.h>

#include <pall/lifo.h>

#include <fsma/fsma.h>

#include "stack.h"
#include "cexit.h"

struct lifo_handler *hll = NULL;	/* Loaded */
struct lifo_handler *hlr = NULL;	/* Results */

void stack_unit_destroy(void *data) {
	struct stack_unit *e = data;

	e->unload(e->arg);
	dlclose(e->handle);

	fsma_free(data);
}

void stack_init(void) {
	if (!(hll = pall_lifo_init(&stack_unit_destroy, NULL, NULL)))
		cexit_failure("pall_lifo_init(): %s\n", strerror(errno));

	if (!(hlr = pall_lifo_init(&stack_unit_destroy, NULL, NULL)))
		cexit_failure("pall_lifo_init(): %s\n", strerror(errno));
}

void stack_destroy(void) {
	pall_lifo_destroy(hll);
	pall_lifo_destroy(hlr);
}

