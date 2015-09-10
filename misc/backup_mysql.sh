#!/bin/bash
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
if [ $# -ne 4 ]; then
	echo "Usage: ${0} <database> <username> <password> <destination directory>"
	exit 1
fi

# Globals
DB_ORIGIN=${1}
DB_USER=${2}
DB_PASS=${3}
DIR_DESTIN=${4}
FIL_DESTIN=${DIR_DESTIN}/${DB_ORIGIN}_$(date +%Y%m%d_%H%M%S).sql.gz

# Verification
if [ -e ${FIL_DESTIN} ]; then
	echo "Destination file already exists."
	exit 1
fi

touch ${FIL_DESTIN} >& /dev/null

if [ $? -ne 0 ]; then
	echo "Cannot write on destination file: ${FIL_DESTIN}"
	exit 1
fi

# Execution
mysqldump -u${DB_USER} -p${DB_PASS} ${DB_ORIGIN} | gzip -cq > ${FIL_DESTIN}

if [ $? -ne 0 ]; then
	echo "Failed to backup database."
	exit 1
fi

# Report
echo "Database backup complete."

# All good
exit 0

