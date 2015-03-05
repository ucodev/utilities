#!/usr/bin/env python
#
# @file logsegv.py
# @brief Convert a syslog segfault entry into human readable data
#
# Date: 05-03-2015
# License: BSD 3-Clause
# 
# Copyright (c) 2015, Pedro A. Hortas (pah@ucodev.org)
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#  - Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
#  - Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
#  - Neither the name of the ucodev.org nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
#
# Project details:
#
#  Home Page:	http://www.ucodev.org
#  Version:	0.01a
#  Portability: GNU/Linux, Python >= 2.6, Python < 3.x
#  Description: Analyzes a syslog segfault entry and tries to dump some human readable data
#               regarding the cause of the crash.
#
#
# Usage example:
#
#    $ ./logsegv.py "Feb 28 19:46:12 localhost kernel: [196586.543197] test[3663]: segfault at 7fde9762e9d0 ip 00007fde9e24a70d sp 00007fde9d639eb0 error 4 in libpthread-2.19.so[7fde9e23d000+19000]"
#    Logsegv v0.01
#    Copyright (c) 2015  Pedro A. Hortas (pah@ucodev.org)
#    Licensed under the BSD 3-Clause license
#    http://www.ucodev.org
#
#    Preliminary findings:
#
#    Ocurred on:        	Feb 28 19:46:12
#    Hostname:          	localhost
#    Process Name:      	test
#    Process ID:        	3663
#    Offending Address: 	0x7fde9762e9d0
#    Register EIP:      	0x7fde9e24a70d
#    Register ESP:      	0x7fde9d639eb0
#    Error cause:       	No page found while reading in user-space context
#    Component Name:    	libpthread-2.19.so
#    Region Base:       	0x7fde9e23d000
#    Region Size:       	0x19000
#    Component Address: 	0xd70d
#
#    Going deeper...
#
#    Offending opcode:  	8b 87 d0 02 00 00   
#    For humans:        	mov 0x2d0(%rdi),%eax
#    Occurred inside:   	pthread_cancel()
#    Somewhere around:  	/build/buildd/eglibc-2.19/nptl/pthread_cancel.c:34
#
#    Nothing more to show
#    $
#

import sys
import os
import re
import commands

### Globals ###
EXIT_SUCCESS = 0
EXIT_FAILURE = 1
DUMP_FILE = "/tmp/.dump.dat"
VERSION = "0.01a"

### Useful stuff ###
class logsegv():
	def error_to_string(self, error):
		error_str = ""

		if error & 0x01:
			error_str += "Protection Fault "
		else:
			error_str += "No page found "

		if error & 0x02:
			error_str += "while writing "
		else:
			error_str += "while reading "

		if error & 0x04:
			error_str += "in user-space context "
		else:
			error_str += "in kernel-space context "

		if error & 0x08:
			error_str += "when performing an instruction fetch"

		return error_str

	def preliminary_data_fetch(self):
		# Parse input
		pat = re.search(r'^(.+)\s+(\S+)\s+kernel:\s+\[\d+\.\d+\]\s+(\S+)\[(\d+)\]: segfault at ([0-9A-Fa-f]+) ip ([0-9A-Fa-f]+) sp ([0-9A-Fa-f]+) error (\d+) in (\S+)\[([0-9A-Fa-f]+)\+([0-9A-Fa-f]+)\]$', self.raw_data);

		# Check if input is valid
		if not pat:
			return None

		# Assign and process values
		self.data = {}
		self.data['date'] = pat.group(1)
		self.data['hostname'] = pat.group(2)
		self.data['process_name'] = pat.group(3)
		self.data['process_id'] = pat.group(4)
		self.data['addr_offend'] = int(pat.group(5), 16)
		self.data['reg_eip'] = int(pat.group(6), 16)
		self.data['reg_esp'] = int(pat.group(7), 16)
		self.data['error'] = int(pat.group(8))
		self.data['component_name'] = pat.group(9)
		self.data['component_base'] = int(pat.group(10), 16)
		self.data['component_size'] = int(pat.group(11), 16)

	def preliminary_data_print(self):
		print("Ocurred on:        \t" + self.data['date'])
		print("Hostname:          \t" + self.data['hostname'])
		print("Process Name:      \t" + self.data['process_name'])
		print("Process ID:        \t" + self.data['process_id'])
		print("Offending Address: \t" + hex(self.data['addr_offend']))
		print("Register EIP:      \t" + hex(self.data['reg_eip']))
		print("Register ESP:      \t" + hex(self.data['reg_esp']))
		print("Error cause:       \t" + self.error_to_string(self.data['error']))
		print("Component Name:    \t" + self.data['component_name'])
		print("Region Base:       \t" + hex(self.data['component_base']))
		print("Region Size:       \t" + hex(self.data['component_size']))
		print("Component Address: \t" + hex(self.data['reg_eip'] - self.data['component_base']))

	def addr_dump_fetch(self, addr):
		cur_func = None
		cur_file = None
		instruction = None
		opcode = None

		with open(DUMP_FILE, "r") as fp:
			for line in fp:
				# Update current function, if required
				pat = re.search("^(\S+\(\))\:$", line)
				if pat:
					cur_func = pat.group(1)
					continue

				# Update current file and line, if required
				pat = re.search("^(/\S+\.c\:\d+)$", line)
				if pat:
					cur_file = pat.group(1)
					continue

				# Check if there's an address match and extract the opcode and canonical
				pat = re.search("^\s+%x\:\s+([0-9A-Fa-f\s]+)\s{2,}(\S+.+)$" % addr, line)
				if pat:
					opcode = pat.group(1)
					instruction = " ".join(filter(None, pat.group(2).split(" ")))
					break

		if not opcode:
			return None

		self.dump = { 'opcode': opcode, 'instruction': instruction, 'cfile': cur_file, 'cfunc': cur_func }

	def addr_dump_print(self):
		print("Offending opcode:  \t" + self.dump['opcode'])
		print("For humans:        \t" + self.dump['instruction'])
		print("Occurred inside:   \t" + self.dump['cfunc'])
		print("Somewhere around:  \t" + self.dump['cfile'])

	def dump_create(self):
		(status, output) = commands.getstatusoutput("objdump -glCD $(ldd `which %s` | grep %s | cut -d' ' -f 3) > %s" % (self.data['process_name'], self.data['component_name'].split('-')[0], DUMP_FILE))

		return status

	def dump_unlink(self):
		try:
			os.unlink(DUMP_FILE)
		except:
			pass

	def product_version(self):
		print("Logsegv v" + VERSION)
		print("Copyright (c) 2015  Pedro A. Hortas (pah@ucodev.org)")
		print("Licensed under the BSD 3-Clause license")
		print("http://www.ucodev.org\n")

	def usage(self):
		if len(sys.argv) != 2:
			print("Usage: %s <syslog segfault string>" % sys.argv[0])
			return EXIT_FAILURE

		self.raw_data = sys.argv[1]

	def do(self):
		# Print some project info
		self.product_version()

		# Check usage
		status = self.usage()

		if status:
			return status

		# Get some preliminary data
		self.preliminary_data_fetch()

		if not self.data:
			print("Unable to parse input.")
			return EXIT_FAILURE

		# Dump some findings
		print("Preliminary findings:\n")
		self.preliminary_data_print()

		# Try to get the real deal
		print("\nGoing deeper...\n")

		# Create dump file
		status = self.dump_create()

		if status:
			print("Unable to acquire more data :(")
			return EXIT_FAILURE

		# Fech data from dump
		self.addr_dump_fetch(self.data['reg_eip'] - self.data['component_base'])

		if not self.dump:
			print("Nothing found :(")
			return EXIT_FAILURE

		# Dump the useful data
		self.addr_dump_print()

		# Nothing more to analyze for now
		print("\nNothing more to show.")

		# Unlink temporary files
		self.dump_unlink()

		return EXIT_SUCCESS


### MAIN ###
if __name__ == "__main__":
	sys.exit(logsegv().do())

