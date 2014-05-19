#!/usr/bin/python
#
# @file dldeps.py
# @brief dynamically linked binary dependencies utility
#
# Date: 24-10-2012
# License: BSD 3-Clause
# 
# Copyright (c) 2012, Pedro A. Hortas (pah@ucodev.org)
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
#  Version:	1.0.1
#  Portability: GNU/Linux, Python >= 2.6, Python < 3.x
#  Description: Analyzes a dynamic executable file, copying it and all its
#		library dependencies into a NEWROOT directory. It also 
#		creates/updates the ld.so.conf and ld.so.cache files located at
#		NEWROOT/etc/. This utility is intended to be used on chroot
#		environment setups.
#

import sys
import os
import re
import commands
import shutil
import stat


# Params
ETC_PATH = "/etc"
LDSOCONF_PATH = ETC_PATH + "/ld.so.conf"
LDD_PATH = "/usr/bin/ldd"
LDCONFIG_PATH = "/sbin/ldconfig"
EXIT_SUCCESS_CODE = 0
EXIT_FAILURE_CODE = 1
LDD_OUTPUT_REGEX = [
	r"^.+=>\s(.+)\s\(.+\)$",
	r"^\s+(/.+)\s\(.+\)$"
]


# Globals
ldep_list = []
ldsoconf_set = set([])
error = None


# Interface
def create_dir_tree(newdir):
	global error

	if not os.path.exists(newdir):
		try:
			os.makedirs(newdir)
		except OSError as e:
			error = e.strerror
			return False

	return True

def process_symlink(lfile, newroot):
	global error

	try:
		st = os.lstat(lfile)
	except OSError as e:
		error = e.strerror
		return None

	if stat.S_ISLNK(st.st_mode):
		lfile_link = lfile
		plf = lfile_link.lstrip("/").split("/")

		if os.readlink(lfile_link)[0] == "/":
			# Absolute
			lfile = os.readlink(lfile_link)
		else:
			# Relative
			lfile = "/" + "/".join(plf[:-1]) + "/" + os.readlink(lfile_link)

		linkdir = newroot + "/" + "/".join(plf[:-1])

		if not create_dir_tree(linkdir):
			return None

		try:
			symlink = newroot + "/" + lfile_link

			if os.path.exists(symlink):
				os.unlink(symlink)

			os.symlink(os.readlink(lfile_link), symlink)
		except OSError as e:
			error = e.strerror
			return None

	return lfile
		
def copy_dlb(dlb, newroot):
	global error

	dlb_file = process_symlink(dlb, newroot)

	if dlb_file == None:
		return False

	newbdir = newroot + "/" + "/".join(dlb_file.lstrip("/").split("/")[:-1])

	if not create_dir_tree(newbdir):
		return False

	try:
		shutil.copy(dlb_file, newbdir)
	except (IOError, Error) as e:
		error = e.strerror
		return False

	return True

def copy_ldeps(newroot):
	global error

	for ldep in ldep_list:
		if not copy_dlb("/" + "/".join(ldep), newroot):
			return False

	return True

def collect_ldeps(output):
	global ldep_list

	ldeps = output.split("\n")

	for lib in ldeps:
		for retry in LDD_OUTPUT_REGEX:
			pat = re.search(retry, lib)
			if pat:
				break

		if not pat:
			continue

		ldep_list.append(tuple(pat.group(1).lstrip("/").split("/")))

def ldsoconf_load(newroot):
	global ldsoconf_set, error

	ldpath = newroot + LDSOCONF_PATH

	if not os.path.exists(newroot + LDSOCONF_PATH):
		if not os.path.exists(newroot + ETC_PATH):
			try:
				os.makedirs(newroot + ETC_PATH)
			except OSError as e:
				error = e.strerror
				return False

		try:
			fp = open(ldpath, "w")
		except IOError as e:
			error = e.strerror
			return False

		fp.close()

		return True

	try:
		fp = open(newroot + LDSOCONF_PATH, "r")
	except IOError as e:
		error = e.strerror
		return False

	try:
		ldcont = fp.read().strip("\n").split("\n")
	except (IOError, ValueError) as e:
		error = e.strerror
		fp.close()
		return False

	for val in ldcont:
		ldsoconf_set.add(val)

	fp.close()

	return True

def ldsoconf_update(newroot):
	global error

	try:
		os.unlink(newroot + LDSOCONF_PATH)
	except OSError as e:
		error = e.strerror
		return False

	try:
		fp = open(newroot + LDSOCONF_PATH, "w+")
	except IOError as e:
		error = e.strerror
		return False

	for val in ldsoconf_set:
		try:
			fp.write(val + "\n")
		except (IOError, ValueError) as e:
			error = e.strerror
			fp.close()
			return False

	fp.close()

	return True

def ldsoconf_set_update():
	global ldsoconf_set

	for dep in ldep_list:
		ldsoconf_set.add("/" + "/".join(dep[:-1]))

def usage(argv):
	print("Usage: %s BINARY NEWROOT\n" % argv[0])
	print("  BINARY\tFull path to dynamic executable file")
	print("  NEWROOT\tNew root directory path\n")
	print("Example:\n")
	print("  # %s /usr/sbin/apache2 /chroot/apache2\n" % argv[0])

	sys.exit(EXIT_FAILURE_CODE)

# Entry point
if __name__ == "__main__":
	if len(sys.argv) != 3:
		usage(sys.argv)

	dlb = sys.argv[1]
	newroot = os.path.realpath(sys.argv[2])

	if not os.path.exists(os.path.realpath(dlb)):
		print("File %s does not exist." % dlb)
		sys.exit(EXIT_FAILURE_CODE)

	if not os.path.exists(LDD_PATH):
		print("File %s does not exist." % LDD_PATH)
		sys.exit(EXIT_FAILURE_CODE)

	if not os.path.exists(LDCONFIG_PATH):
		print("File %s does not exist." % LDCONFIG_PATH)
		sys.exit(EXIT_FAILURE_CODE)

	(status, output) = commands.getstatusoutput(LDD_PATH + " " + dlb)

	if status:
		print("Warning: %s isn't a dynamic executable." % dlb)

		if not copy_dlb(dlb, newroot):
			print("Failed to copy %s to %s: %s" % (dlb, newroot, error))
			sys.exit(EXIT_FAILURE_CODE)

		print("Success (with warnings).")
		sys.exit(EXIT_SUCCESS_CODE)

	collect_ldeps(output)

	if not ldsoconf_load(newroot):
		print("Failed to create or load %s: %s" % (newroot + LDSOCONF_PATH, error))
		sys.exit(EXIT_FAILURE_CODE)

	ldsoconf_set_update()

	if not copy_ldeps(newroot):
		print("Failed to copy library dependencies: %s", error)
		sys.exit(EXIT_FAILURE_CODE)

	if not ldsoconf_update(newroot):
		print("Unable to update file %s: %s" % (newroot + LDSOCONF_PATH, error))
		sys.exit(EXIT_FAILURE_CODE)

	(status, output) = commands.getstatusoutput(LDCONFIG_PATH + " -r " + newroot)

	if status:
		print("%s returned exit status %d:\n" % LDCONFIG_PATH, status)
		print(output)
		sys.exit(EXIT_FAILURE_CODE)

	if not copy_dlb(dlb, newroot):
		print("Failed to copy %s to %s: %s" % (dlb, newroot, error))
		sys.exit(EXIT_FAILURE_CODE)

	print("Success.")

	sys.exit(EXIT_SUCCESS_CODE)

