#!/usr/bin/env python
#
# @file sedit.py
# @brief A simple scriptable edit tool
#
# Date: 05-10-2015
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
#  Version:	0.02a
#  Portability: Python >= 2.6, Python < 3.x
#  Description: Allow scripts to add, change or remove content from on the specified file.
#  Deps:	Python modules 'sys', 'os', 'shutil' and 're'
#
#  Usage examples:
#
#  # ./sedit.py /etc/rc.local add '# After shebang line' after '^#!/bin/.+'
#  # ./sedit.py /etc/rc.local add '# This is a comment' before 'exit 0'
#  # ./sedit.py /etc/rc.local add '#!/bin/sh' at line#1
#  # ./sedit.py /etc/rc.local delete '^# This is a.+$'
#  # ./sedit.py /etc/rc.local change 'exit 0' with 'echo 'Exiting...'; exit 0;'
#

import sys
import os
import shutil
import re

EXIT_SUCCESS = 0
EXIT_FAILURE = 1

class Failure():
	error_msg = "FAILURE"
	error_code = EXIT_FAILURE

	def __init__(self, error_msg, error_code = EXIT_FAILURE):
		self.error_msg = error_msg
		self.error_code = error_code
		self.do(error_msg, error_code)

	def do(self, error_msg, error_code):
		output = "FAILURE: %s (Code: %s).\n" % (error_msg, error_code)
		sys.stderr.write(output)
		sys.exit(error_code)

class Status():
	code = None

class Output():
	output = list()

	def do(self):
		# Backup file
		shutil.copyfile(runtime["input"].target, runtime["input"].target + ".sedit.bak")

		# Unlink file
		os.unlink(runtime["input"].target)

		# Recreate file
		with open(runtime["input"].target, "w+") as f:
			f.write("".join(self.output))

		os.unlink(runtime["input"].target + ".sedit.bak")
	
class Input():
	target = None
	op = None
	what = None
	where = None
	content = None

	def target_count_lines(self):
		with open(self.target) as f:
			return len(f.readlines())

	def validate(self):
		if len(sys.argv) < 4:
			print("Usage: %s <file> [add|delete|change|replace] <string|regex> [after|before|with|at] <string|regex|line#n>" % sys.argv[0])
			sys.exit(EXIT_FAILURE)

		if sys.argv[2] not in ("add", "change", "replace", "delete"):
			Failure("Unrecognized operation: %s" % sys.argv[2])

		if len(sys.argv) != 4 and len(sys.argv) != 6:
			Failure("Invalid number of arguments.")

		if len(sys.argv) == 6 and sys.argv[4] not in ("after", "before", "with", "at"):
			Failure("Unrecognized position indicator: %s" % sys.argv[4])
			
	def decode(self):
		self.target = sys.argv[1]
		self.op = sys.argv[2]
		self.what = sys.argv[3]
		if len(sys.argv) > 4:
			self.where = sys.argv[4]
			self.content = sys.argv[5]

	def do(self):
		self.validate()
		self.decode()

class Process():
	ignore_next = False
	line_count = 0

	def line(self, line):
		if runtime["input"].op == "delete" or runtime["input"].op == "change":
			# Check if there's a match on 'what'
			pat = re.search(runtime["input"].what, line)

			if not pat:
				# No match, no fire
				runtime["output"].output.append(line)
				return
		elif runtime["input"].where != "at" and runtime["input"].where != "with":
			# Check if there's a match on 'content'
			pat = re.search(runtime["input"].content, line)

			if not pat:
				# No match, no fire
				runtime["output"].output.append(line)
				return
		elif runtime["input"].where == "at":
			# Check if we're at the specified line number
			if int(runtime["input"].content.split('#')[1]) != self.line_count:
				runtime["output"].output.append(line)
				return
		elif runtime["input"].where == "with":
			pass
		else:
			Failure("Invalid position indicator: %s." % runtime["input"].where)

		# Fire up the operation
		if runtime["input"].op == "add":
			if runtime["input"].where == "after":
				# Add after the match
				runtime["output"].output.append(line)
				runtime["output"].output.append(runtime["input"].what + "\n")
			elif runtime["input"].where == "before":
				# Add before the match
				runtime["output"].output.append(runtime["input"].what + "\n")
				runtime["output"].output.append(line)
			elif runtime["input"].where == "at":
				# Add at the line
				if int(runtime["input"].content.split('#')[1]) == self.line_count:
					runtime["output"].output.append(runtime["input"].what + "\n")
					runtime["output"].output.append(line)
			else:
				Failure("Invalid position indicator in for 'add' operation: %s" % runtime["input"].where)

			return

		if runtime["input"].op == "delete":
			# Ignore this line
			return

		if runtime["input"].op == "change":
			# The 'change' differs from replace as the 'what' is a regex, not a string
			if runtime["input"].where == "with":
				# Replace the contents of 'what' with 'content'
				runtime["output"].output.append(runtime["input"].content + "\n")
			else:
				Failure("Operation 'change' must be used along with 'with'.")

		if runtime["input"].op == "replace":
			if runtime["input"].where == "with":
				# Replace the contents of 'what' with 'content'
				runtime["output"].output.append(line.replace(runtime["input"].what, runtime["input"].content))
			elif runtime["intut"].where == "at":
				# Replace the contents of this line with 'what'
				if int(runtime["input"].content.split('#')[1]) == self.line_count:
					runtime["output"].output.append(runtime["input"].what)
			else:
				Failure("Operation 'change' must be used along with 'at' or 'with'.")

	def crawl(self):
		with open(runtime["input"].target) as f:
			for line in f.readlines():
				if not line:
					break

				self.line_count += 1

				# Check if the next line should be ignored
				if self.ignore_next == True:
					self.ignore_next = False
					continue

				self.line(line)

	def do(self):
		self.crawl()
		runtime["status"].code = EXIT_SUCCESS

class Main():
	exit_status = EXIT_FAILURE

	def do(self):
		runtime["input"].do()
		runtime["process"].do()

		# print output
		runtime["output"].do()

		if runtime["status"].code == None:
			raise Exception("Status code wasn't changed. Internal error.")

		self.exit_status = EXIT_SUCCESS #runtime["status"].code

class Runtime():
	def load(self):
		global runtime

		runtime["main"] = Main()
		runtime["input"] = Input()
		runtime["output"] = Output()
		runtime["status"] = Status()
		runtime["process"] = Process()

runtime = {
	"main": None,
	"input": None,
	"output": None,
	"status": None,
	"process": None
}

# Entry Point
if __name__ == "__main__":
	# Load runtime
	try:
		Runtime().load()
	except Exception as e:
		Failure(str(e))

	# Execute main
	try:
		runtime["main"].do()
	except Exception as e:
		Failure(str(e))

	# Exit gracefully
	sys.exit(runtime["main"].exit_status)

