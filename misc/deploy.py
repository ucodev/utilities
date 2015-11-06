#!/usr/bin/env python
#
# @file deploy.py
# @brief A simple instrumentation tool based on JSON templates
#
# Date: 06-11-2015
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
#  Description: A simple instrumentation tool based on JSON templates.
#  Deps:	Python modules 'sys', 'os', 'subprocess' and 'json'
#
#  Usage examples:
#
#  # ./deploy.py deployable.json
#
#  - Check file deployable.json for a template example
#  - Check file deployable.list for a batch example
#

import sys
import os
import json
import subprocess

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
		with open(runtime["input"].template_file + ".sh", "w+") as f:
			f.write("\n".join(self.output))

		os.chmod(runtime["input"].template_file + ".sh", 0755)

		subprocess.call([runtime["input"].template_file + ".sh"])

		os.unlink(runtime["input"].template_file + ".sh")

class Input():
	template_file = None
	template_content = None

	def validate(self):
		if len(sys.argv) != 2:
			print("Usage: %s <template>" % sys.argv[0])
			sys.exit(EXIT_FAILURE)

		self.template_file = sys.argv[1]

	def decode(self):
		with open(self.template_file) as f:
			self.template_content = json.loads(f.read())

	def do(self):
		self.validate()
		self.decode()

class Process():
	def import_commands(self, procedure):
		if type(procedure["commands"]) == list:
			return procedure["commands"]
		elif type(procedure["commands"]) in (str, unicode):
			with open(procedure["commands"]) as f:
				procedure["commands"] = list()

				for line in f.readlines():
					if not line:
						break

					if line[0] == "\n":
						continue

					procedure["commands"].append(line)

			return procedure["commands"]
		else:
			Failure("Invalid type for procedure commands detected: %s" % str(type(procedure["commands"])))

	def deploy(self):
		# Shebang Line
		runtime["output"].output.append("#!%s" % runtime["input"].template_content["context"]["shell"])
		# Header to stdout
		runtime["output"].output.append("echo -e \"Deploying '%s' version %s.\\n\"" % (runtime["input"].template_content["context"]["name"], runtime["input"].template_content["context"]["version"]))
		# Header to logfile
		runtime["output"].output.append("echo -e \"\\n[`date`]: Deploying '%s' version %s.\" >> %s" % (runtime["input"].template_content["context"]["name"], runtime["input"].template_content["context"]["version"], runtime["input"].template_content["context"]["log"]))

		# Procedures
		for procedure in runtime["input"].template_content["procedures"]:
			# Add procedure description as a comment
			runtime["output"].output.append("# %s" % procedure["description"])
			# Show the progress message
			runtime["output"].output.append("echo -n \"%s... \"" % procedure["message"])
			# Import procedure commands if required
			procedure["commands"] = self.import_commands(procedure)

			# Process procedure commands
			for command in procedure["commands"]:
				# Prepend execution data to log file
				runtime["output"].output.append("echo \"[`date`]: Executing [ %s ]...\" >> %s" % (command, runtime["input"].template_content["context"]["log"]))
				# Check if output should be shown
				if procedure["output"]:
					runtime["output"].output.append("(%s) 2>&1 | tee -a %s; test ${PIPESTATUS[0]} -eq %d" % (command, runtime["input"].template_content["context"]["log"], procedure["expect"]))
				else:
					# Execute command and redirect output to log file
					runtime["output"].output.append("(%s) &>> %s" % (command, runtime["input"].template_content["context"]["log"]))
				# Check if the return status is the one being expected
				runtime["output"].output.append("if [ $? -ne %d ]; then echo Failed.; exit 1; fi" % procedure["expect"])
				# Append execution status to log file
				runtime["output"].output.append("echo \"[`date`]: Successfully executed [ %s ].\" >> %s" % (command, runtime["input"].template_content["context"]["log"]))
			# If we've reached this point, everything is good.
			runtime["output"].output.append("echo OK.")

		# Inform that everything went fine.
		runtime["output"].output.append("echo -e \"\\nFinished processing '%s'.\"" % runtime["input"].template_content["context"]["name"])

	def do(self):
		self.deploy()
		runtime["status"].code = EXIT_SUCCESS

class Main():
	exit_status = EXIT_FAILURE

	def do(self):
		runtime["input"].do()
		runtime["process"].do()
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

