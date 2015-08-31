#!/bin/sh
#
#  Copyright (c) 2015, Pedro A. Hortas (pah@ucodev.org)
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without modification,
#  are permitted provided that the following conditions are met:
#
#  1. Redistributions of source code must retain the above copyright notice,
#     this list of conditions and the following disclaimer.
#
#  2. Redistributions in binary form must reproduce the above copyright notice,
#     this list of conditions and the following disclaimer in the documentation
#     and/or other materials provided with the distribution.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
#  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
#  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
#  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
#  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
#  OF THE POSSIBILITY OF SUCH DAMAGE.
#

# Usage
if [ ${#} -ne 1 ]; then
	echo "Usage: ${0} <file to encrypt>"
	exit 1
fi

# Globals
FIL_ORIGIN=${1}
FIL_DESTIN=${FIL_ORIGIN}.enc

# Verification
touch ${FIL_DESTIN}

if [ $? -ne 0 ]; then
	echo "Unable to write destination file: ${FIL_DESTIN}"
	exit 1
fi

# Encrypt
openssl aes-256-cbc -salt -in ${FIL_ORIGIN} -out ${FIL_DESTIN}

# Validate
if [ $? -ne 0 ]; then
	echo "Failed to encrypt file: ${FIL_ORIGIN}"
	exit 1
fi

# All good
echo "File was successfully encrypted (AES-256-CBC): ${FIL_DESTIN}"
exit 0

