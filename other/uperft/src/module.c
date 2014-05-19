/**
 * @file module.c
 * @brief uPerfT modules interface.
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
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>
#include <dlfcn.h>

#include <pall/lifo.h>

#include <fsma/fsma.h>

#include <fsop/dir.h>
#include <fsop/file.h>
#include <fsop/path.h>

#include "stack.h"
#include "cexit.h"
#include "module.h"

static char *_modules_dir = NULL;

static void _module_load(const char *path) {
	char *dlerr = NULL;
	struct stack_unit *e = NULL;

	if (!(e = fsma_malloc(sizeof(struct stack_unit))))
		cexit_failure("malloc(): %s\n", strerror(errno));

	if (!(e->handle = dlopen(path, RTLD_NOW)))
		cexit_failure("dlopen(): %s\n", dlerror());

	*(void **) (&e->load) = dlsym(e->handle, SYMBOL_PERFT_MODULE_LOAD);

	if ((dlerr = dlerror()))
		cexit_failure("dlsym(e->handle, \"%s\"): %s\n", SYMBOL_PERFT_MODULE_LOAD, dlerr);

	*(void **) (&e->unload) = dlsym(e->handle, SYMBOL_PERFT_MODULE_UNLOAD);

	if ((dlerr = dlerror()))
		cexit_failure("dlsym(e->handle, \"%s\"): %s\n", SYMBOL_PERFT_MODULE_UNLOAD, dlerr);

	*(void **) (&e->run) = dlsym(e->handle, SYMBOL_PERFT_MODULE_RUN);

	if ((dlerr = dlerror()))
		cexit_failure("dlsym(e->handle, \"%s\"): %s\n", SYMBOL_PERFT_MODULE_RUN, dlerr);

	*(void **) (&e->name) = dlsym(e->handle, SYMBOL_PERFT_MODULE_NAME);

	if ((dlerr = dlerror()))
		cexit_failure("dlsym(e->handle, \"%s\"): %s\n", SYMBOL_PERFT_MODULE_NAME, dlerr);

	e->arg = e->load();

	hll->push(hll, e);
}

static int _module_load_action(int order, const char *fpath, const char *rpath, void *arg) {
	if (order != FSOP_WALK_INORDER)
		return 0;

	if (!fsop_path_isreg(fpath))
		return 0;

	_module_load(fpath);

	return 0;
}

static void _module_load_all(void) {
	fsop_walkdir(_modules_dir, NULL, &_module_load_action, NULL);
}

void module_set_dir(const char *dir) {
	if (!(_modules_dir = fsma_malloc(strlen(dir) + 1)))
		cexit_failure("fsma_malloc(): %s\n", strerror(errno));

	strcpy(_modules_dir, dir);
}

void module_init(void) {
	_module_load_all();
}

void module_destroy(void) {
	fsma_free(_modules_dir);
}

