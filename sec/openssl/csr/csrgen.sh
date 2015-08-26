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

if [ $# -ne 5 ]; then
	echo "Usage: ${0} <CN> <Organization Name> <Organization Unit> <Country> <cipher:bits>"
	echo ""
	echo "Example:"
	echo ""
	echo -e "\t$ ${0} www.ucodev.org 'uCodev' IT PT rsa:2048"
	echo ""
	exit 1
fi

CN=${1}
O=${2}
OU=${3}
C=${4}
BITS=${5}

openssl req -nodes -out ${CN}.csr -newkey ${BITS} -keyout ${CN}.key -subj "/C=${C}/O=${O}/OU=${OU}/CN=${CN}"

if [ $? -ne 0 ]; then
	echo "Failed to generate CSR."
	exit 1
fi

echo ""
echo "CSR and KEY successfully created:"
echo -e "\tDN: c=${C}, O=${O}, CN=${CN}"
echo ""

exit 0

