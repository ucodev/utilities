/**
 * @file export.h
 * @brief uPerfT export interface header.
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


#ifndef PERFT_EXPORT_H
#define PERFT_EXPORT_H

#include "stack.h"

void export_set_csv(const char *file);
void export_init(void);
void export_destroy(void);
void export_data(struct stack_unit *e);

#endif

