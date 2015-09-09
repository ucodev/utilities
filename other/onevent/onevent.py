#!/usr/bin/python
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
#  Fork me on GitHub:
#  	https://github.com/ucodev
#

import sys
import json
import commands
import datetime

EXIT_SUCCESS = 0
EXIT_FAILURE = 1

# Class: Debug handler
class Debug:
	def dump(self, msg):
		sys.stdout.write("[" + str(datetime.datetime.now()) + "]: " + str(msg) + "\n")

# Class: Failure handler
class Fail:
	error_code = None
	error_msg = ""

	def do(self):
		print(self.error_msg)
		sys.exit(self.error_code)

# Class: Configuration handler
class Config:
	argc = 2
	filename = "/etc/onevent.conf"
	data = {}

	def load(self):
		try:
			with open(self.filename) as f:
				self.data = json.loads(f.read())
		except IOError as e:
			fail.error_msg = str(e)
			fail.error_code = EXIT_FAILURE
			fail.do()

	def do(self):
		self.load()

# Class: Command line processor
class Cmdline:
	def check(self):
		if len(sys.argv) > config.argc:
			fail.error_msg = "Usage: %s <config file>" % sys.argv[0]
			fail.error_code = EXIT_FAILURE
			fail.do()

	def process(self):
		if len(sys.argv) == 2:
			config.filename = sys.argv[1]

	def do(self):
		self.check()
		self.process()

# Class: Event handler
class Events:
	actions = None

	def process(self):
		for event in self.actions:
			# Check for the event
			debug.dump("EVENT: Checking for occurrences through: %s" % event)

			(status, output) = commands.getstatusoutput(event)

			if status:
				debug.dump("EVENT: no occurrences.")
				continue

			# Peform the action
			debug.dump("ACTION: Performing action: %s" % self.actions[event])

			(status, output) = commands.getstatusoutput(self.actions[event])

			if status:
				debug.dump("ACTION: Failed\n[\nStatus: %s\nOutput:\n%s\n]" % (status, output))
				continue

			debug.dump("DONE: Event: %s -> Action: %s" % (event, self.actions[event]))

	def do(self):
		self.actions = config.data
		self.process()


# MAIN: Entry point
if __name__ == "__main__":
	# Instantiate objects
	debug = Debug()
	fail = Fail()
	config = Config()
	cmdline = Cmdline()
	events = Events()

	# Execute object procedures in the right order
	cmdline.do()

	config.do()

	events.do()

	debug.dump("Done")

