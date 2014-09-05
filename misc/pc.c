/**
 * @file pc.c
 * @brief Portable C - An architecture-specific configuration header generator
 *
 * Date: 05-09-2014
 * License: BSD 3-Clause
 * 
 * Copyright (c) 2014, Pedro A. Hortas (pah@ucodev.org)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  - Neither the name of the ucodev.org nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 *
 * Project details:
 *
 *  Home Page:   http://www.ucodev.org
 *  Version:     0.01a
 *  Portability: C99, C11
 *  Description: Creates a C configuration header for the running architecture.
 *
 * Compilation instructions:
 *
 *  $ cc -o pc pc.c
 *
 * Usage:
 *
 *  $ ./pc > config.h
 *
 */

#include <stdio.h>

int determine_sizes(void) {
	unsigned char s8 = 0, s16 = 0, s32 = 0, s64 = 0, s128 = 0;

	printf("#define ARCH_BITS %zu\n", sizeof(void *) << 3);
	printf("#define LITTLE_ENDIAN %u\n", (*(unsigned char *) (unsigned int [1]) { 1 }) == 1);
	printf("#define BIG_ENDIAN %u\n", (*(unsigned char *) (unsigned int [1]) { 1 }) == 0);

	if (sizeof(char) == 1) {
		puts("typedef char pc_sint8_t;");
		puts("typedef unsigned char pc_uint8_t;");
		s8 = 1;
	}

	if (sizeof(short) == 2) {
		puts("typedef short pc_sint16_t;");
		puts("typedef unsigned short pc_uint16_t;");
		s16 = 1;
	}

	if (sizeof(int) == 4) {
		puts("typedef int pc_sint32_t;");
		puts("typedef unsigned int pc_uint32_t;");
		s32 = 1;
	} else if (sizeof(long) == 4) {
		puts("typedef long pc_sint32_t;");
		puts("typedef unsigned long pc_uint32_t;");
		s32 = 1;
	}

	if (sizeof(long) == 8) {
		puts("typedef long pc_sint64_t;");
		puts("typedef unsigned long pc_uint64_t;");
		s64 = 1;
	} else if (sizeof(long long) == 8) {
		puts("typedef long long pc_sint64_t;");
		puts("typedef unsigned long long pc_uint64_t;");
		s64 = 1;
	}

	if (sizeof(long long) == 16) {
		puts("typedef long long s128_t;");
		puts("typedef unsigned long long u128_t;");
		s128 = 1;
	}

#ifdef __GNUC__
	else {
		puts("typedef signed pc_sint128_t __attribute__((mode(TI)));");
		puts("typedef unsigned pc_uint128_t __attribute__((mode(TI)));");
		s128 = 1;
	}
#endif

	switch (sizeof(void *)) {
		case 1:  puts("typedef pc_sint8_t pc_sintptr_t;");
			 puts("typedef pc_uint8_t pc_uintptr_t;");
			 break;
		case 2:  puts("typedef pc_sint16_t pc_sintptr_t;");
			 puts("typedef pc_uint16_t pc_uintptr_t;");
			 break;
		case 4:  puts("typedef pc_sint32_t pc_sintptr_t;");
			 puts("typedef pc_uint32_t pc_uintptr_t;");
			 break;
		case 8:  puts("typedef pc_sint64_t pc_sintptr_t;");
			 puts("typedef pc_uint64_t pc_uintptr_t;");
			 break;
		case 16: puts("typedef pc_sint128_t pc_sintptr_t;");
			 puts("typedef pc_uint128_t pc_uintptr_t;");
			 break;
	}

	if (!s8) puts("#warning Cannot determine a type with size of 8 bits.");
	if (!s16) puts("#warning Cannot determine a type with size of 16 bits.");
	if (!s32) puts("#warning Cannot determine a type with size of 32 bits.");
	if (!s64) puts("#warning Cannot determine a type with size of 64 bits.");
	if (!s128) puts("#warning Cannot determine a type with size of 128 bits.");

	return 0;
}

int main(void) {
	puts("#ifndef CONFIG_H");
	puts("#define CONFIG_H");

	determine_sizes();

	puts("#endif");

	return 0;
}

