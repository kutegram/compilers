#
# Copyright (c) 2006-2011 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
# This component and the accompanying materials are made available
# under the terms of the License "Eclipse Public License v1.0"
# which accompanies this distribution, and is available
# at the URL "http://www.eclipse.org/legal/epl-v10.html".
#
# Initial Contributors:
# Nokia Corporation - initial contribution.
#
# Contributors:
#
# Description: 
# raptor_make module
# This module contains the classes that write and call Makefile wrappers.
#

import hashlib
import os
import pickle
import random
import raptor
import raptor_timing
import raptor_utilities
import raptor_version
import raptor_data
import re
import subprocess
import time
from raptor_makefile import *
import traceback
import sys
from xml.sax.saxutils import escape
from xml.sax.saxutils import unescape


class BadMakeEngineException(Exception):
	pass

class CannotWriteMakefileException(Exception):
	pass

def string_following(prefix, str):
	"""If str starts with prefix then return the rest of str, otherwise None"""
	if str.startswith(prefix):
		return str[len(prefix):]
	else:
		return None

def XMLEscapeLog(stream):
	""" A generator that reads a raptor log from a stream and performs an XML escape
	    on all text between tags, which is usually make output that could contain
	    illegal characters that upset XML-based log parsers.
	    This function yields "xml-safe" output line by line.
	"""
	inRecipe = False

	for line in stream:
		if line.startswith("<recipe"):
			inRecipe = True
		elif line.startswith("</recipe"):
			inRecipe = False
			
		# unless we are inside a "recipe", any line not starting
		# with "<" is free text that must be escaped.
		if inRecipe or line.startswith("<"):
			yield line
		else:
			yield escape(line)

def AnnoFileParseOutput(annofile):
	""" A generator that extracts log output from an emake annotation file, 
	    perform an XML-unescape on it and "yields" it line by line.  """
	if isinstance(annofile,str):
		af = open(annofile, "r")
	else:
		af = annofile

	inOutput = False

	buildid = ""
	duration = "unknown"
	availability = "unknown"
	for line in af:
		line = line.rstrip("\n\r")


		if not inOutput:
			o = string_following("<output>", line)
			if not o:
				o = string_following('<output src="prog">', line)

			if o:
				inOutput = True	
				yield unescape(o)+'\n'
				continue


			o = string_following('<build id="',line)
			if o:
				buildid = o[:o.find('"')]
				yield "Starting build: "+buildid+"\n"
				continue 

			o = string_following('<metric name="duration">', line)
			if o:
				total_secs = int(float(o[:o.find('<')]))
				if total_secs != 0:
					duration = "{mins:.0f}:{secs}".format(mins = total_secs/60, secs = total_secs % 60)
				else:
					duration = "0:0"
				continue 


			o = string_following('<metric name="clusterAvailability">', line)
			if o:
				availability = o[:o.find('<')]
				continue 
				
		else:
			end_output = line.find("</output>")
		
			if end_output != -1:
				line = line[:end_output]
				inOutput = False
			
			if line != "":	
				yield unescape(line)+'\n'

	yield "Finished build: {0}   Duration: {1} (m:s)   Cluster availability: {2}%\n".format(buildid, duration, availability)
	af.close()


def run_make(make_process):
	""" A function to run make command. This is in a standalone function so
		Raptor could easily use multiprocess to run multiple make programs
	"""
	makeenv = os.environ.copy()
	makeenv['TALON_RECIPEATTRIBUTES'] = make_process.talon_recipeattributes
	makeenv['TALON_SHELL'] = make_process.talon_shell
	makeenv['TALON_BUILDID'] = make_process.talon_buildid
	makeenv['TALON_TIMEOUT'] = make_process.talon_timeout

	if make_process.filesystem == "unix":
		p = subprocess.Popen(
				args = [make_process.command], 
				bufsize = 65535,
				stdout = subprocess.PIPE,
				stderr = subprocess.STDOUT,
				close_fds = True, 
				shell = True,
				env = makeenv)
	else:
		p = subprocess.Popen(
				args = [make_process.shell, '-c', make_process.command],
				bufsize = 65535,
				stdout = subprocess.PIPE,
				stderr = subprocess.STDOUT,
				shell = False,
				universal_newlines = True, 
				env = makeenv)

	# When using an [emake] annotation file all the output from make is redirected
	# to .stdout and .stderr files. Those files are read when the make process exits
	# and only then is the output passed on to the filters. We still read from the
	# subprocess pipe here in case there is any unexpected output from the shell
	# that might block the subprocess.
	#
	# Without an annotation file, make errors are still redirected to a .stderr
	# file since we don't really care about seeing them immediately. But standard
	# output is not redirected, it is read from the subprocess pipe and passed
	# to the filters immediately so that users can see the build progressing.
	
	stream = p.stdout
	for line in XMLEscapeLog(stream):
		if not make_process.copyLogFromAnnoFile:
			make_process.logstream.write(line)
  
	make_process.returncode = p.wait()
	make_process.hasrun = True

	return make_process.returncode



class MakeProcess(object):
	""" A process of make program """
	def __init__(self, command):
		self.command = command
		self.hasrun = False # Has this process been executed
		self.returncode = 255 # default to error


# raptor_make module classes
class MakeEngine(object):

	def __init__(self, Raptor, engine="make_engine"):
		self.raptor = Raptor
		self.valid = True
		self.descrambler = None
		self.descrambler_started = False
		self.global_make_variables = {}
		
		# look for an alias first as this gives end-users a chance to modify
		# the shipped variant rather than completely replacing it.
		if engine in Raptor.cache.aliases:
			avar = Raptor.cache.FindNamedAlias(engine)
		elif engine in Raptor.cache.variants:
			avar = Raptor.cache.FindNamedVariant(engine)
		else:
			raise BadMakeEngineException("'{0}' does not appear to be a make engine - no settings found for it".format(engine))

		if not avar.isDerivedFrom("make_engine", Raptor.cache):
			raise BadMakeEngineException("'{0}' is not a build engine (it's a variant but it does not extend 'make_engine')".format(engine))
					
		# find the variant and extract the values
		try:
			units = avar.GenerateBuildUnits(Raptor.cache)
			evaluator = Raptor.GetEvaluator( None, units[0] , gathertools=True)

			# shell
			self.shellpath = evaluator.Get("DEFAULT_SHELL")
			self.talonshell = str(evaluator.Get("TALON_SHELL"))
			self.talontimeout = str(evaluator.Get("TALON_TIMEOUT"))
			self.talonretries = str(evaluator.Get("TALON_RETRIES"))
			
			# work around for RVCT 2.2 failed compiles
			delete_on_failed_compile_s = evaluator.Get("DELETE_ON_FAILED_COMPILE")
			self.delete_on_failed_compile = ""
			if delete_on_failed_compile_s is not None and delete_on_failed_compile_s != "":
				self.delete_on_failed_compile = "1"

			# commands
			self.initCommand = evaluator.Get("initialise")
			self.buildCommand = evaluator.Get("build")
			self.shutdownCommand = evaluator.Get("shutdown")

			# options
			self.makefileOption = evaluator.Get("makefile")
			self.keepGoingOption = evaluator.Get("keep_going")
			self.jobsOption = evaluator.Get("jobs")
			self.defaultMakeOptions = evaluator.Get("defaultoptions")

			# Logging
			#  copylogfromannofile means, for emake, that we should ignore 
			# emake's console output and instead extract output from its annotation
			# file.  This is a workaround for a problem where some emake
			# console output is lost.  The annotation file has a copy of this
			# output in the "parse" job and it turns out to be uncorrupted.
			self.copyLogFromAnnoFile = (evaluator.Get("copylogfromannofile") == "true")
			self.emakeCm = (len([opt for opt in self.raptor.makeOptions if opt.startswith("--emake-cm")]) > 0)
			self.annoFileName = None # store the anno file name

			if self.copyLogFromAnnoFile:
				try:
					self.annoFileName = string_following("--emake-annofile=", [opt for opt in self.raptor.makeOptions if opt.startswith("--emake-annofile")][0])
					self.raptor.Info("annofile: " + self.annoFileName)
				except IndexError, bad_index:
					cannot_use_anno_msg = "Cannot copy log from annotation file as no annotation filename was specified via the option --mo=--emake-annofile=<filename>"
					if self.emakeCm:
						self.raptor.Error(cannot_use_anno_msg) # Only an error if requested use of cm
					else:
						self.raptor.Info(cannot_use_anno_msg)
					self.copyLogFromAnnoFile = False

			# buffering
			self.scrambled = (evaluator.Get("scrambled") == "true")

			# check tool versions
			Raptor.CheckToolset(evaluator, avar.name)
			
			# default targets (can vary per-invocation)
			self.defaultTargets = Raptor.defaultTargets

			# work out how to split up makefiles
			try:
				selectorNames = [ x.strip() for x in evaluator.Get("selectors").split(',') if x.strip() != "" ]
				self.selectors = []


				if len(selectorNames) > 0:
					for name in selectorNames:
						pattern = evaluator.Get(name.strip() + ".selector.iface")
						target = evaluator.Get(name.strip() + ".selector.target")
						ignoretargets = evaluator.Get(name.strip() + ".selector.ignoretargets")
						self.selectors.append(MakefileSelector(name,pattern,target,ignoretargets))
			except KeyError:
				Raptor.Error("{0}.selector.iface, {0}.selector.target not found in make engine configuration".format(name))
				self.selectors = []

		except KeyError:
			self.valid = False
			raise BadMakeEngineException("Bad '{0}' configuration found.".format(engine))

		# there must at least be a build command...
		if not self.buildCommand:
			self.valid = False
			raise BadMakeEngineException("No build command for '{0}'".format(engine))


	def Write(self, toplevel, specs, configs):
		"""Generate a set of makefiles, or one big Makefile."""

		if not self.valid:
			return None

		talon_settings="""
TALON_SHELL:={0}
TALON_TIMEOUT:={1}
TALON_RECIPEATTRIBUTES:=\
 name='$$RECIPE'\
 target='$$TARGET'\
 host='$$HOSTNAME'\
 layer='$$COMPONENT_LAYER'\
 component='$$COMPONENT_NAME'\
 bldinf='$$COMPONENT_META' mmp='$$PROJECT_META'\
 config='$$SBS_CONFIGURATION' platform='$$PLATFORM'\
 phase='$$MAKEFILE_GROUP' source='$$SOURCE'
export TALON_RECIPEATTRIBUTES TALON_SHELL TALON_TIMEOUT
USE_TALON:={2}

""".format(self.talonshell, self.talontimeout, "1")

		timing_start = "$(info " + \
				raptor_timing.Timing.custom_string(tag = "start",
				object_type = "makefile", task = "parse",
				key = "$(THIS_FILENAME)",
				time="$(shell date +%s.%N)").rstrip("\n") + ")"
				
		timing_end = "$(info " + \
				raptor_timing.Timing.custom_string(tag = "end",
				object_type = "makefile", task = "parse",
				key = "$(THIS_FILENAME)",
				time="$(shell date +%s.%N)").rstrip("\n") + ")"


		# Debugging on or off for make:
		# We need it at the very top level so that it can be used
		# to determine what extra info to put in recipe tags
		try:
			flmdebug_setting = os.environ["FLMDEBUG"]
		except KeyError:
			flmdebug_setting = ""

		# global variables are set at the top of each makefile
		self.global_make_variables['HOSTPLATFORM'] = " ".join(raptor.hostplatform)
		self.global_make_variables['HOSTPLATFORM_DIR'] = raptor.hostplatform_dir
		self.global_make_variables['HOSTPLATFORM32_DIR'] = raptor.hostplatform32_dir
		self.global_make_variables['OSTYPE'] = self.raptor.filesystem
		self.global_make_variables['FLMHOME'] = str(self.raptor.systemFLM)
		self.global_make_variables['SHELL'] = self.shellpath
		self.global_make_variables['DELETE_ON_FAILED_COMPILE'] = raptor_utilities.make_bool_string(self.delete_on_failed_compile)
		self.global_make_variables['NO_DEPEND_GENERATE'] = raptor_utilities.make_bool_string(self.raptor.noDependGenerate)
		
		self.makefile_prologue = """

# generated by {0} {1}

HOSTPLATFORM:={2}
HOSTPLATFORM_DIR:={3}
HOSTPLATFORM32_DIR:={4}
OSTYPE:={5}
FLMHOME:={6}
SHELL:={7}
THIS_FILENAME:=$(firstword $(MAKEFILE_LIST))
DELETE_ON_FAILED_COMPILE:={8} 

{9}
FLMDEBUG:={10}

include {11}

""" .format(     raptor.name, raptor_version.fullversion(),
		 self.global_make_variables['HOSTPLATFORM'],
		 self.global_make_variables['HOSTPLATFORM_DIR'],
		 self.global_make_variables['HOSTPLATFORM32_DIR'],
		 self.global_make_variables['OSTYPE'],
		 self.global_make_variables['FLMHOME'],
		 self.global_make_variables['SHELL'],
		 self.global_make_variables['DELETE_ON_FAILED_COMPILE'],
		 talon_settings,
		 flmdebug_setting,
		 self.raptor.systemFLM.Append('globals.mk') )

		
		
		# Unless dependency processing has been eschewed via the CLI, use a .DEFAULT target to
		# trap missing dependencies (ignoring user config files that we know are usually absent)
		if not (self.raptor.noDependGenerate or self.raptor.noDependInclude):
			self.makefile_prologue += """

$(FLMHOME)/user/final.mk:
$(FLMHOME)/user/default.flm:
$(FLMHOME)/user/globals.mk:

.DEFAULT::
	@echo "<warning>Missing dependency detected: $@</warning>"

"""

		# Only output timings if requested on CLI
		if self.raptor.timing:
			self.makefile_prologue += "\n# Print Start-time of Makefile parsing\n" \
					+ timing_start + "\n\n"
	
	
			self.makefile_epilogue = "\n\n# Print End-time of Makefile parsing\n" \
				+ timing_end + "\n"
		else:
			self.makefile_epilogue = ""

		self.makefile_epilogue += """

include {0} 

""".format(self.raptor.systemFLM.Append('final.mk') )


		self.raptor.Debug("Writing Makefile '{0}'".format(str(toplevel)))

		self.toplevel = toplevel

		# create the top-level makefiles
		makefileset = None

		try:
			makefileset = MakefileSet(directory = str(toplevel.Dir()),
										   selectors = self.selectors,
										   filenamebase = str(toplevel.File()),
										   prologue = self.makefile_prologue,
										   epilogue = self.makefile_epilogue,
										   defaulttargets = self.defaultTargets)

			# are we pruning duplicates?
			self.prune = self.raptor.pruneDuplicateMakefiles
			self.hashes = set()

			# are we writing one Makefile or lots?
			self.many = not self.raptor.writeSingleMakefile

			# add a makefile for each spec under each config
			config_makefileset = makefileset
			for c in configs:
				if self.many:
					config_makefileset = makefileset.createChild(c.name)

				# make sure the config_wide spec item is put out first so that it
				# can affect everything.
				ordered_specs=[]
				config_wide_spec = None
				for s in specs:
					if s.name == "config_wide":
						config_wide_spec = s
					else:
						ordered_specs.append(s)

				if config_wide_spec is not None:
					config_wide_spec.Configure(c, cache = self.raptor.cache)
					self.WriteConfiguredSpec(config_makefileset, config_wide_spec, c, True)

				for s in ordered_specs:
					s.Configure(c, cache = self.raptor.cache)
					self.WriteConfiguredSpec(config_makefileset, s, c, False)

			makefileset.close()
		except Exception,e:
			tb = traceback.format_exc()
			if not self.raptor.debugOutput:
				tb=""
			self.raptor.Error("Failed to write makefile '{0}': {1} : {2}".format(str(toplevel),str(e),tb))
			raise CannotWriteMakefileException(str(e))

		return makefileset


	def WriteConfiguredSpec(self, parentMakefileSet, spec, config, useAllInterfaces):
		# ignore this spec if it is empty
		hasInterface = spec.HasInterface()
		childSpecs = spec.GetChildSpecs()

		if not hasInterface and not childSpecs:
			return

		parameters = []
		dupe = True
		pickled = False
		iface = None
		guard = None
		if hasInterface:
			# find the Interface (it may be a ref)
			try:
				iface = spec.GetInterface(self.raptor.cache)

			except raptor_data.MissingInterfaceError, e:	
				self.raptor.Error("No interface for '{0}'".format(spec.name))
				return

			if iface.abstract:
				self.raptor.Error("Abstract interface '{0}' for '{1}'".format(
								  iface.name, spec.name))
				return

			# we need to guard the FLM call with a hash based on all the
			# parameter values so that duplicate calls cannot be made.
			# So we need to find all the values before we can write
			# anything out.
			md5hash = hashlib.md5()
			md5hash.update(iface.name)

			# we need an Evaluator to get parameter values for this
			# Specification in the context of this Configuration
			evaluator = self.raptor.GetEvaluator(spec, config)

			def addparam(k, value, default):
				if value == None:
					if p.default != None:
						value = p.default
					else:
						self.raptor.Error("{0} undefined for '{1}'".format(
										  k, spec.name))
						value = ""

				parameters.append((k, value))
				md5hash.update(value)

			# parameters required by the interface
			for p in iface.GetParams(self.raptor.cache):
				val = evaluator.Resolve(p.name)
				addparam(p.name,val,p.default)

			# Use Patterns to fetch a group of parameters
			for g in iface.GetParamGroups(self.raptor.cache):
				for k,v in evaluator.ResolveMatching(g.patternre):
					addparam(k,v,g.default)

			hash = md5hash.hexdigest()
			dupe = hash in self.hashes

			self.hashes.add(hash)
			
			# pickled interfaces need the bld.inf output directory even
			# if it is not an FLM parameter (and it normally isn't)
			pickled = iface.isPickled(self.raptor.cache)
			if pickled:
				bldinfop = evaluator.Resolve("BLDINF_OUTPUTPATH")
				if not bldinfop:
					self.raptor.Error("BLDINF_OUTPUTPATH is required in {0} for pickled interfaces".format(config.name))
					
		# we only create a Makefile if we have a new FLM call to contribute,
		# OR we are not pruning duplicates (guarding instead)
		# OR we have some child specs that need something to include them.
		if dupe and self.prune and not childSpecs:
			return

		makefileset = parentMakefileSet
		# Create a new layer of makefiles?
		if self.many:
			makefileset = makefileset.createChild(spec.name)

		if not (self.prune and dupe):
			if self.prune:
				guard = ""
			else:
				guard = "guard_" + hash

		# generate the call to the FLM
		if iface is not None and not dupe:
			# pickled interfaces save the parameters in a separate file
			# and add a parameter which points at that file's location.
			if pickled:
				self.pickleParameters(parameters, hash, bldinfop)
				
			# add the FLM call to the selected makefiles
			makefileset.addCall(spec.name, config.name, iface.name, useAllInterfaces, iface.GetFLMIncludePath(self.raptor.cache), parameters, guard)

		# recursive includes

		for child in childSpecs:
			self.WriteConfiguredSpec(makefileset, child, config, useAllInterfaces)

		if self.many:
			makefileset.close() # close child set of makefiles as we'll never see them again.

	def pickleParameters(self, parameters, hash, directory):
		"""write a pickle of the parameter dictionary to directory/hash/pickle."""
		if not parameters or not hash or not directory:
			return
		
		dictionary = dict(parameters)
		
		# create a combined hash of the FLM parameters and the global variables
		# as we add the globals to the parameter dictionary we just made.
		md5hash = hashlib.md5()
		md5hash.update(hash)
		
		for k in sorted(self.global_make_variables.keys()):
			value = self.global_make_variables[k]
			md5hash.update(k + value)
			dictionary[k] = value
			
		planbdir = directory + "/" + md5hash.hexdigest()
		if not os.path.isdir(planbdir):
			try:
				os.makedirs(planbdir)
			except:
				self.raptor.Error("could not create directory " + planbdir)
				return
		
		filename = os.path.join(planbdir, "pickle")
		
		# if the file already exists then it is automatically up to date
		# because the name contains a hash of the contents.
		if not os.path.isfile(filename):
			
			try:
				file = open(filename, "wb")
				pickle.dump(dictionary, file, protocol=2)
				file.close()
			except:
				self.raptor.Error("could not create file " + filename)
			
		parameters.append(("PLANBDIR", planbdir))
		
	def Make(self, makefileset, build_zero_flmcall_makefiles = False):
		"run the make command"

		if not self.valid:
			return False
	
		# Always use Talon since it does the XML not
		# just descrambling
		if not self.StartTalon() and not self.raptor.keepGoing:
			self.Tidy()
			return False
			
		# run any initialisation script
		if self.initCommand:
			self.raptor.Info("Running {0}".format(self.initCommand))
			if os.system(self.initCommand) != 0:
				self.raptor.Error("Failed in {0}".format(self.initCommand))
				self.Tidy()
				return False

		# Save file names to a list, to allow the order to be reversed
		if build_zero_flmcall_makefiles:
			makefile_sequence = makefileset.makefiles
			self.raptor.Debug ("Makefiles to build: {0}".format(str([f.filename for f in makefile_sequence])))
		else:
			makefile_sequence = makefileset.nonempty_makefiles()
			self.raptor.Debug ("Makefiles with non-zero flm call counts: {0}".format(str([f.filename for f in makefile_sequence])))

		# Iterate through args passed to raptor, searching for CLEAN or REALLYCLEAN
		clean_flag = False
		for arg in self.raptor.args:
			clean_flag = ("CLEAN" in self.raptor.args) or \
			            ("REALLYCLEAN" in self.raptor.args)

		# Files should be deleted in the opposite order to the order
		# they were built. So reverse file order if cleaning.
		# For len() etc to work we need to create a list 
		# - not just an iterator which is what reversed() returns.
		if clean_flag:
			makefile_sequence = [m for m in reversed(makefile_sequence)]

		# Report number of makefiles to be built
		self.raptor.InfoDiscovery(object_type = "makefile", count = len(makefile_sequence))


		# Stores all the make processes that were executed:
		make_processes = []
		
		return_state = True

		# Process each file in turn
		for makefile in makefile_sequence:
			makefilename = str(makefile.filename)

			if not os.path.exists(makefilename):
				self.raptor.Info("Skipping makefile {0}".format(makefilename))
				continue
			self.raptor.Info("Making {0}".format(makefilename))
			# assemble the build command line
			command = self.buildCommand

			if self.makefileOption:
				command += ' {0}  "{1}" '.format(self.makefileOption, makefilename)

			if self.raptor.keepGoing and self.keepGoingOption:
				command += " " + self.keepGoingOption

			if self.raptor.jobs > 1 and self.jobsOption:
				command += " {0} {1}".format(self.jobsOption,str(self.raptor.jobs))

			# Set default options first so that they can be overridden by
			# ones set by the --mo option on the raptor commandline:
			command += " " + self.defaultMakeOptions
			# Can supply options on the commandline to override default settings.
			if len(self.raptor.makeOptions) > 0:
				for o in self.raptor.makeOptions:
					if o.find(";") != -1 or  o.find("\\") != -1:
						command += "  '{0}'".format(o)
					else:
						command += "  {0}".format(o)

			# Switch off dependency file including?
			if self.raptor.noDependInclude or self.raptor.noDependGenerate:
				command += " NO_DEPEND_INCLUDE=1"
			
			# Switch off dependency file generation (and, implicitly, inclusion)?
			if self.raptor.noDependGenerate:
				command += " NO_DEPEND_GENERATE=1"
			
			command += ' TALON_DESCRAMBLE=' 
			if self.scrambled:
				command += '1 '
			else:
				command += '0 '
			
			# use the retry mechanism if requested
			if self.raptor.tries > 1:
				command += ' RECIPETRIES={0}'.format(self.raptor.tries)
				command += ' TALON_RETRIES={0}'.format(self.raptor.tries - 1)

			# targets go at the end, if the makefile supports them
			addTargets = self.raptor.targets[:]
			ignoreTargets = makefile.ignoretargets
			if addTargets and ignoreTargets:
				for target in self.raptor.targets:
					if re.match(ignoreTargets, target):
						addTargets.remove(target)

			if addTargets:
				command += " " + " ".join(addTargets)

			# Send stderr to a file so that it can't mess up the log (e.g.
			# clock skew messages from some build engines scatter their
			# output across our xml.
			stderrfilename = makefilename+'.stderr'
			stdoutfilename = makefilename+'.stdout'
			command += " 2>'{0}' ".format(stderrfilename)

			# Keep a copy of the stdout too in the case of using the 
			# annofile - so that we can trap the problem that
			# makes the copy-log-from-annofile workaround necessary
			# and perhaps determine when we can remove it.
			if self.copyLogFromAnnoFile:
				command += " >'{0}' ".format(stdoutfilename)

			# Substitute the makefile name for any occurrence of #MAKEFILE#
			command = command.replace("#MAKEFILE#", makefilename)

			# Substitute the makefile stage for any occurrence of #STAGE#
			# e.g. --history=ncp_#STAGE#.hist might become
			#      --history=ncp_export.hist
			command = command.replace("#STAGE#", makefile.name)

			self.raptor.Info("Executing '{0}'".format(command))

			# Create a process of make program
			mproc = MakeProcess(command)
			mproc.makefile = str(makefilename)
			mproc.talon_recipeattributes = "none"
			mproc.talon_shell = self.talonshell
			mproc.talon_buildid = str(self.buildID)
			mproc.talon_timeout = str(self.talontimeout)
			mproc.filesystem = self.raptor.filesystem
			mproc.logstream = self.raptor.out
			mproc.copyLogFromAnnoFile = self.copyLogFromAnnoFile
			mproc.stderrfilename = stderrfilename
			mproc.stdoutfilename = stdoutfilename
			mproc.shell = raptor_data.ToolSet.shell

			make_processes.append(mproc)

			if self.copyLogFromAnnoFile:
				mproc.annoFileName = self.annoFileName.replace("#MAKEFILE#", makefilename)
			
			# execute the build.
			# the actual call differs between Windows and Unix.
			# bufsize=1 means "line buffered"
			try:
				# Time the build
				self.raptor.InfoStartTime(object_type = "makefile",
					task = "build", key = str(makefilename))

				run_make(mproc)

				if mproc.returncode != 0:
					return_state = False
					if not self.raptor.keepGoing:
						break
				
			except Exception,e:
				self.raptor.Error("Exception '{0}' during '{1}'".format(str(e), command))
				break
			finally:
				# Still report end-time of the build
				self.raptor.InfoEndTime(object_type = "makefile", task = "build",
									    key = str(makefilename))


		# Getting all the log output copied into files
		for mproc in make_processes:
			# Don't try to get log results if we never actually ran make.
			if not mproc.hasrun:
				continue 

			if self.copyLogFromAnnoFile:
				annofilename = mproc.annoFileName.replace("#MAKEFILE#", makefilename)
				self.raptor.Info("copylogfromannofile: Copying log from annotation file {0} to work around a potential problem with the console output".format(annofilename))
				try:
					for l in XMLEscapeLog(AnnoFileParseOutput(annofilename)):
						mproc.logstream.write(l)
				except Exception,e:
					sys.stderr.write("Couldn't complete stdout output from annofile {0} for {1} - '{2}'\n".format(annofilename, command, str(e)))
				
			# Take all the stderr output that went into the .stderr file
			# and put it back into the log, but safely so it can't mess up
			# xml parsers.
			try:
				e = open(mproc.stderrfilename,"r")
				for line in e:
					self.raptor.out.write(escape(line))
				e.close()
			except Exception,e:
				sys.stderr.write("Couldn't complete stderr output for {0} - '{1}'\n".format(mproc.command, str(e)))

		# run any shutdown script
		if self.shutdownCommand != None and self.shutdownCommand != "":
			self.raptor.Info("Running {0}".format(self.shutdownCommand))
			if os.system(self.shutdownCommand) != 0:
				self.raptor.Error("Failed in {0}".format(self.shutdownCommand))
				return_state = False

		self.Tidy()
		return return_state

	def Tidy(self):
		"clean up after the make command"
		self.StopTalon() 

	def StartTalon(self):
		# the talon command
		beginning = raptor.hostplatform_dir + "/bin"
		if "win" in raptor.hostplatform:
			end = ".exe"
		else:
			end = ""
			
		self.talonctl = str(self.raptor.home.Append(beginning, "talonctl"+end))
			
		# generate a unique build number
		random.seed()
		looking = True
		tries = 0
		while looking and tries < 100:
			self.buildID = raptor.name + str(random.getrandbits(32))
			
			command = self.talonctl + " start"

			os.environ["TALON_BUILDID"] = self.buildID
			self.raptor.Info("Running {0}".format(command))
			looking = (os.system(command) != 0)
			tries += 1
		if looking:
			self.raptor.Error("Failed to initialise the talon shell for this build")
			self.talonctl = ""
			return False
		
		return True
	
	def StopTalon(self):
		if self.talonctl:
			command = self.talonctl + " stop"
			self.talonctl = ""
			
			self.raptor.Info("Running {0}".format(command))
			if os.system(command) != 0:
				self.raptor.Error("Failed in {0}".format(command))
				return False
			
		return True
	
	def StartDescrambler(self):
		# the descrambler command
		beginning = raptor.hostplatform_dir + "/bin"
		if "win" in raptor.hostplatform:
			end = ".exe"
		else:
			end = ""

		self.descrambler = str(self.raptor.home.Append(beginning, "sbs_descramble"+end))
			
		# generate a unique build number
		random.seed()
		looking = True
		tries = 0
		while looking and tries < 100:
			buildID = raptor.name + str(random.getrandbits(32))

			command = self.descrambler + " " + buildID + " start"
			self.raptor.Info("Running {0}".format(command))
			looking = (os.system(command) != 0)
			tries += 1

		if looking:
			self.raptor.Error("Failed to start the log descrambler")
			self.descrambler_started = True
			return False

		self.descrambler_started = True
		self.descrambler +=	" " + buildID

		return  True

	def StopDescrambler(self):
		if self.descrambler_started:
			command = self.descrambler + " stop"
			self.descrambler = ""

			self.raptor.Info("Running {0}".format(command))
			if os.system(command) != 0:
				self.raptor.Error("Failed in {0}".format(command))
				return False
		return True
	
# end of the raptor_make module
