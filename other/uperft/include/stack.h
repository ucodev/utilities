/**
 * @file stack.h
 * @brief uPerfT stack interface header.
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


#ifndef PERFT_STACK_H
#define PERFT_STACK_H

#include <pall/lifo.h>

/* Data structures */
struct stack_unit {
	char *name;
	void *handle;
	void *(*load) (void);
	void (*unload) (void *arg);
	int (*run) (void *arg);
	void *arg;
	unsigned long loops;
	unsigned long errors;
	long double avg_time;
	long double total_time;
};

/* External variables */
extern struct lifo_handler *hll;
extern struct lifo_handler *hlr;

/* Prototypes */
void stack_unit_destroy(void *data);
void stack_init(void);
void stack_destroy(void);

#endif
