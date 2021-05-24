#!/bin/bash
#
#  Copyright (c) 2015-2021, Pedro A. Hortas (pah@ucodev.org)
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

strip_lslashes() {
	echo ${1#/}
}

strip_rslashes() {
	echo ${1%/}
}

strip_slashes() {
	str=$(strip_lslashes ${1}) && strip_rslashes ${str}
}

replace_slashes() {
	echo ${1} | sed -e 's/\//_/g'
}

# Usage check
if [ $# -ne 3 ]; then
	echo "Usage: ${0} <origin directory> <destination directory> <plain key file>"
	exit 1
fi

# Globals
DIR_ORIGIN=$(strip_rslashes ${1})
DIR_DESTIN=$(strip_rslashes ${2})
FIL_DESTIN=${DIR_DESTIN}/$(replace_slashes `strip_slashes ${DIR_ORIGIN}`)_$(date +%Y%m%d_%H%M%S).tar.gz
FIL_PLNKEY=${3}

# Verification
if [ -e ${FIL_DESTIN} ]; then
	echo "Destination file already exists."
	exit 1
fi

if ! [ -e ${DIR_ORIGIN} ]; then
	echo "Source directory doesn't exist."
	exit 1
fi

if ! [ -e ${DIR_DESTIN} ]; then
	echo "Destination directory doesn't exist."
	exit 1
fi

if ! [ -e ${FIL_PLNKEY} ]; then
	echo "Plain key file doesn't exist."
	exit 1
fi

touch ${FIL_DESTIN} >& /dev/null

if [ $? -ne 0 ]; then
	echo "Cannot write on destination directory: ${DIR_DESTIN}"
	exit 1
fi

# Execution
tar zcf - ${DIR_ORIGIN} 2> /dev/null | openssl enc -e -aes-256-cbc -salt -md sha512 -pbkdf2 -iter 100000 -pass file:${FIL_PLNKEY} -out ${FIL_DESTIN} >& /dev/null

# Reporting
if [ $? -ne 0 ]; then
	rm -f ${FIL_DESTIN}
	echo "Backup failed."
	exit 1
fi

echo "Backup successful."

# All good
exit 0

