/**
 * @file main.c
 * @brief uPerfT main.
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


#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/resource.h>

#include "stack.h"
#include "module.h"
#include "unit.h"
#include "result.h"
#include "export.h"
#include "cexit.h"

#include <fsop/path.h>

static void _init(void) {
	stack_init();

	module_init();

	export_init();
}

static void _run(void) {
	unit_test();

	result_dump();
}

static void _destroy(void) {
	export_destroy();

	module_destroy();

	stack_destroy();
}

static void _prio_set_nice(int prio) {
	int inc_prio = prio + getpriority(PRIO_PROCESS, 0);

	if (nice(inc_prio) != prio)
		cexit_failure("nice(%d): %s\n", inc_prio, strerror(errno));
}

static void _usage_process(int argc, char **argv) {

	if ((argc < 2) || (argc > 5))
		cexit_failure("Usage: %s <modules dir> [ <nice prio> ] [ <nr loops> ] [ <csv file> ]\n", argv[0]);

	if (!fsop_path_exists(argv[1]))
		cexit_failure("The path \'%s\' doesn\'t exist.\n", argv[1]);

	if (!fsop_path_isdir(argv[1]))
		cexit_failure("The path \'%s\' isn\'t a directory.\n", argv[1]);

	module_set_dir(argv[1]);

	if (argc >= 3)
		_prio_set_nice(atoi(argv[2]));

	if (argc >= 4)
		unit_set_loops(strtoul(argv[3], NULL, 10));

	if (argc == 5)
		export_set_csv(argv[4]);
}

int main(int argc, char *argv[]) {
	_usage_process(argc, argv);

	_init();

	_run();

	_destroy();

	return 0;
}

