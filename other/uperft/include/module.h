/**
 * @file module.h
 * @brief uPerfT modules interface header.
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


#ifndef PERFT_MODULE_H
#define PERFT_MODULE_H

/* Definitions */
#define SYMBOL_PERFT_MODULE_NAME	"perft_name"
#define SYMBOL_PERFT_MODULE_LOAD	"perft_load"
#define SYMBOL_PERFT_MODULE_UNLOAD	"perft_unload"
#define SYMBOL_PERFT_MODULE_RUN		"perft_run"

/* Prototypes */
void module_set_dir(const char *dir);
void module_init(void);
void module_destroy(void);

#endif
