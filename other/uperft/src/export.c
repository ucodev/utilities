/**
 * @file export.c
 * @brief uPerfT export interface.
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

#include <fsma/fsma.h>

#include "stack.h"
#include "cexit.h"

static char *_export_file = NULL;
static FILE *_export_fp = NULL;

void export_set_csv(const char *file) {
	if (!(_export_file = fsma_malloc(strlen(file) + 1)))
		cexit_failure("fsma_malloc(): %s\n", strerror(errno));

	strcpy(_export_file, file);
}

void export_init(void) {
	if (!_export_file)
		return;

	if (!(_export_fp = fopen(_export_file, "w+")))
		cexit_failure("fopen(\"%s\", \"w+\"): %s\n", strerror(errno));

	fprintf(_export_fp, "Unit Name;Iterations;Avg. Time (usec);Total Time (msec);Errors\n");
}

void export_destroy(void) {
	if (_export_file) {
		fclose(_export_fp);
		fsma_free(_export_file);
	}
}

void export_data(struct stack_unit *e) {
	if (_export_fp)
		fprintf(_export_fp, "%s;%lu;%Lf;%Lf;%lu\n", e->name, e->loops, e->avg_time, e->total_time, e->errors);
}

