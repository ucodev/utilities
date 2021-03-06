/**
 * @file pmo.c
 * @brief PMO - A portable memory operations interface
 *
 * Date: 08-09-2014
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
 *  Version:     0.01d
 *  Portability: C99, C11
 *  Description: An interface for portable memory operations
 *
 * Compilation instructions:
 *
 *  $ cc -std=c99 -fstrict-aliasing -pedantic -Wall -Werror -O2 -c pmo.c
 *
 */

#include <string.h>
#include <stdint.h>

static inline int _pmo_is_little(void) {
	uint16_t u = 1;
	unsigned char v[2];

	memcpy(v, &u, 2);

	return v[0];
}

/* Vector to uint */
static inline void _pmo_memcpy_v2uint_fwd(const unsigned char *v, void *uintf, size_t len) {
	memcpy(uintf, v, len);
}

static inline void _pmo_memcpy_v2uint_rev(const unsigned char *v, void *uintr, size_t len) {
	unsigned int i = 0;
	unsigned char uintr_tmp[len];

	for (i = 0; i < len; i ++)
		uintr_tmp[i ^ (len - 1)] = v[i];

	memcpy(uintr, uintr_tmp, len);
}

void pmo_memcpy_vect2word_little(const unsigned char *v, uint16_t *word) {
	if (_pmo_is_little()) {
		_pmo_memcpy_v2uint_fwd(v, word, 2);
	} else {
		_pmo_memcpy_v2uint_rev(v, word, 2);
	}
}

void pmo_memcpy_vect2word_big(const unsigned char *v, uint16_t *word) {
	if (_pmo_is_little()) {
		_pmo_memcpy_v2uint_rev(v, word, 2);
	} else {
		_pmo_memcpy_v2uint_fwd(v, word, 2);
	}
}

void pmo_memcpy_vect2dword_little(const unsigned char *v, uint32_t *dword) {
	if (_pmo_is_little()) {
		_pmo_memcpy_v2uint_fwd(v, dword, 4);
	} else {
		_pmo_memcpy_v2uint_rev(v, dword, 4);
	}
}

void pmo_memcpy_vect2dword_big(const unsigned char *v, uint32_t *dword) {
	if (_pmo_is_little()) {
		_pmo_memcpy_v2uint_rev(v, dword, 4);
	} else {
		_pmo_memcpy_v2uint_fwd(v, dword, 4);
	}
}

void pmo_memcpy_vect2qword_little(const unsigned char *v, uint64_t *qword) {
	if (_pmo_is_little()) {
		_pmo_memcpy_v2uint_fwd(v, qword, 8);
	} else {
		_pmo_memcpy_v2uint_rev(v, qword, 8);
	}
}

void pmo_memcpy_vect2qword_big(const unsigned char *v, uint64_t *qword) {
	if (_pmo_is_little()) {
		_pmo_memcpy_v2uint_rev(v, qword, 8);
	} else {
		_pmo_memcpy_v2uint_fwd(v, qword, 8);
	}
}

/* uint to vector */
static inline void _pmo_memcpy_uint2vect_fwd(const void *uintf, unsigned char *v, size_t len) {
	memcpy(v, uintf, len);
}

static inline void _pmo_memcpy_uint2vect_rev(const void *uintr, unsigned char *v, size_t len) {
	unsigned int i = 0;
	unsigned char uintr_tmp[len];

	memcpy(uintr_tmp, uintr, len);

	for (i = 0; i < len; i ++)
		v[i ^ (len - 1)] = uintr_tmp[i];
}

void pmo_memcpy_word2vect_little(const uint16_t *word, unsigned char *v) {
	if (_pmo_is_little()) {
		_pmo_memcpy_uint2vect_fwd(word, v, 2);
	} else {
		_pmo_memcpy_uint2vect_rev(word, v, 2);
	}
}

void pmo_memcpy_word2vect_big(const uint16_t *word, unsigned char *v) {
	if (_pmo_is_little()) {
		_pmo_memcpy_uint2vect_rev(word, v, 2);
	} else {
		_pmo_memcpy_uint2vect_fwd(word, v, 2);
	}
}

void pmo_memcpy_dword2vect_little(const uint32_t *dword, unsigned char *v) {
	if (_pmo_is_little()) {
		_pmo_memcpy_uint2vect_fwd(dword, v, 4);
	} else {
		_pmo_memcpy_uint2vect_rev(dword, v, 4);
	}
}

void pmo_memcpy_dword2vect_big(const uint32_t *dword, unsigned char *v) {
	if (_pmo_is_little()) {
		_pmo_memcpy_uint2vect_rev(dword, v, 4);
	} else {
		_pmo_memcpy_uint2vect_fwd(dword, v, 4);
	}
}

void pmo_memcpy_qword2vect_little(const uint64_t *qword, unsigned char *v) {
	if (_pmo_is_little()) {
		_pmo_memcpy_uint2vect_fwd(qword, v, 8);
	} else {
		_pmo_memcpy_uint2vect_rev(qword, v, 8);
	}
}

void pmo_memcpy_qword2vect_big(const uint64_t *qword, unsigned char *v) {
	if (_pmo_is_little()) {
		_pmo_memcpy_uint2vect_rev(qword, v, 8);
	} else {
		_pmo_memcpy_uint2vect_fwd(qword, v, 8);
	}
}

