#!/usr/bin/env python

# This file is part of the Nokia Qt SDK
# 
# Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
# 
# Contact:  Nokia Corporation (qt-info@nokia.com)
#  
# GNU Lesser General Public License Usage
# This file may be used under the terms of the GNU Lesser General Public
# License version 2.1 as published by the Free Software Foundation and
# appearing in the file LICENSE.LGPL included in the packaging of this file.
# Please review the following information to ensure the GNU Lesser General
# Public License version 2.1 requirements will be met:
# http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
# 
# If you have questions regarding the use of this file, please contact Nokia
# at qt-info@nokia.com.

import os
import optparse
import csv
import sys
import subprocess
import warnings

fields = ['RECIPE', 'LABEL','DIRECTORY','SYMBIAN_VERSION']
qtsdk_path = None
symbian_tools_path = None
default_instance_root = None
instance_root = None
recipe_dict = None

class CustomIndentedHelpFormatter (optparse.IndentedHelpFormatter):
	'''Format help with indented section bodies.
	   We are only overriding how the epilog is formatted.
	'''
	def format_epilog(self, epilog):
		if epilog:
			return '\n' + epilog + '\n'
		else:
			return ''

def init():
	global qtsdk_path
	global default_instance_root
	global instance_root
	global symbian_tools_path
	start = os.getcwd()
	os.chdir(os.path.join('..', '..'))
	qtsdk_path = os.getcwd()
	os.chdir(start)
	default_instance_root = os.path.join(qtsdk_path, 'Symbian', 'SDKs')
	instance_root = default_instance_root
	symbian_tools_path = os.path.join(qtsdk_path, 'Symbian', 'tools')
	
def get_recipes(reader):
	recipes = []
	for dict in reader:
		recipe = dict['RECIPE'].strip()
		if recipe:
			recipes.append(recipe)
	if not recipes:
		recipes = None
	return recipes

def strip_fields(reader):
	stripped_fields = []
	for field in reader.fieldnames:
		stripped_fields.append(field.strip())
	reader.fieldnames = stripped_fields

def strip_values():
	keys = recipe_dict.keys()
	for key in keys:
		value = recipe_dict[key]
		if isinstance(value, str):
			stripped_value = value.strip()
		elif isinstance(value, list):
			stripped_value = []
			for item in value:
				stripped_value.append(item.strip())
		else:
			stripped_value = None
		recipe_dict[key] = stripped_value
	
def are_headers_ok(headers):
	if not headers:
		return False
	stripped_fields = []
	for field in headers:
		stripped_fields.append(field.strip())
	return frozenset(fields).issubset(frozenset(stripped_fields))
	
def get_optparse_attr(recipes_file):
	usage = '%prog [options] RECIPE [FILE]'
	description = \
	'Creates a Symbian instance and registers it to QtCreator. ' + \
	'Instance to create is defined via a RECIPE, which can be one of the ' + \
	'defined recipes available in %s, ' % os.path.relpath(recipes_file) + \
	'or via a user-defined recipes FILE. ' \
	'[NOTE]: QtCreator must be restarted for the new Qt Version to appear.'
	epilog_header = 'Defined detected recipes are:'
	epilog_body = None
	if os.path.isfile(recipes_file):
		reader = csv.DictReader(open(recipes_file), restkey='ZIP_LIST')
		if are_headers_ok(reader.fieldnames):
			for dict in reader:
				recipe = dict['RECIPE'].strip()
				if recipe:
					if not epilog_body:
						epilog_body = ''
					epilog_body += '\n[%(rec)s] %(lab)s' \
						% {'rec': recipe, 'lab': dict['LABEL'].strip()}
	if not epilog_body:
		epilog_body = '\nNone'
	epilog = epilog_header + epilog_body
	return (usage, description, epilog, CustomIndentedHelpFormatter())
	
def process_input():
	reader = None
	recipes = None
	recipes_file = os.path.join(symbian_tools_path, 'recipes', 'recipes.csv')
	if not os.path.isfile(recipes_file):
		warnings.warn('No such a file: %s. User-defined recipes FILE will have to be provided.' \
			% os.path.relpath(recipes_file))
	else:
		reader = csv.DictReader(open(recipes_file), restkey='ZIP_LIST')
		if not are_headers_ok(reader.fieldnames):
			warnings.warn('In %(fl)s: headers should be %(hd)s' \
				% {'fl': os.path.relpath(recipes_file), 'hd': fields})
		else:
			strip_fields(reader)
			recipes = get_recipes(reader)
	(usg, des, epl, hf) = get_optparse_attr(recipes_file)
	parser = optparse.OptionParser(usage=usg, description=des, epilog=epl, formatter=hf)
	parser.add_option('-d', dest = 'instance_dir',
	                  help = '''Directory local to %s where instance will be created.
					            If not specified, is defined by recipe.
								If directory exists then it must be empty.
								If directory does not exists then it will be created.''' % instance_root)
	parser.add_option('-n', dest = 'instance_label',
	                  help = '''Instance label to be displayed in QtCreator.
					            If not specified, is defined by recipe.''')
	(options, args) = parser.parse_args()
	if 0 < len(args) < 3:
		if len(args) == 2:
			recipes = None
			recipes_file = args[1]
			if not os.path.isfile(recipes_file):
				parser.error('No such a FILE: %s. Please, provide a recipes FILE.' % recipes_file)
			reader = csv.DictReader(open(recipes_file), restkey='ZIP_LIST')
			if not are_headers_ok(reader.fieldnames):
				parser.error('In user-defined %(fl)s: headers should be %(hd)s' \
					% {'fl': recipes_file, 'hd': fields})
			strip_fields(reader)
			recipes = get_recipes(reader)
	else:
		parser.print_help()
		sys.exit()
	recipe = args[0]
	if not recipes:
		parser.error('In %s: there are not recipes to work with.' % recipes_file)
	if not recipe in recipes:
		parser.error('Incorrect recipe, please, select one from %s' % recipes)
	reader = csv.DictReader(open(recipes_file), restkey='ZIP_LIST')
	strip_fields(reader)
	#TODO: What if we have duplicated recipes? The first found is used.
	global recipe_dict
	recipe_dict = None
	for dict in reader:
		if recipe == dict['RECIPE'].strip():
			recipe_dict = dict
			break
	#print recipe, recipe_dict
	strip_values()
	#print recipe, recipe_dict
	instance_label = options.instance_label
	if instance_label:
		recipe_dict['LABEL'] = instance_label
	instance_path = None
	instance_dir = options.instance_dir
	if instance_dir:
		recipe_dict['DIRECTORY'] = instance_dir
	instance_path = os.path.join(instance_root, recipe_dict['DIRECTORY'])
	if os.path.isdir(instance_path) and os.listdir(instance_path):
		parser.error('Directory %(dir)s is not empty, please, specify a different directory for recipe %(rec)s.' \
			% {'dir': recipe_dict['DIRECTORY'], 'rec': recipe})
	
def create_instance():
	cache_path = os.path.join(qtsdk_path, 'Symbian', 'cache')
	zip_tool = os.path.join(symbian_tools_path, '7za', '7za.exe')
	if not recipe_dict['DIRECTORY']:
		sys.exit('Directory was not specified for recipe %s.' % recipe_dict['RECIPE'])
	instance_path = os.path.join(instance_root, recipe_dict['DIRECTORY'])
	target = '-o' + instance_path
	if not 'ZIP_LIST' in recipe_dict:
		sys.exit('There are no zip files for recipe %s.' % recipe_dict['RECIPE'])
	zip_file = None
	source = None
	commands = []
	nonfiles = []
	for zip_file in recipe_dict['ZIP_LIST']:
		if not zip_file:
			#ignore empty values
			continue
		source = os.path.join(cache_path, zip_file)
		if os.path.isfile(source):
			commands.append([zip_tool, 'x', source, target, '-aoa'])
		else:
			nonfiles.append(zip_file)
	if nonfiles:
		sys.exit('In recipe %(rec)s, following files were not found %(nf)s' \
			% {'rec': recipe_dict['RECIPE'], 'nf': nonfiles})
	if not commands:
		sys.exit('No zip files were found for recipe %s.' % recipe_dict['RECIPE'])
	#Defaulting to sbs in case no Symbian version is specified.
	if recipe_dict['SYMBIAN_VERSION'] == 'Symbian^1':
		zip_file = 'qmake_path_patcher_abld.7z'
	else:
		zip_file = 'qmake_path_patcher_sbsv2.7z'
	source = os.path.join(cache_path, zip_file)
	if not os.path.isfile(source):
		sys.exit('File not found: %s.' % zip_file)
	commands.append([zip_tool, 'x', source, target, '-aoa'])
	#TODO: What if zip tool cannot handle the zip file?
	for command in commands:
		subprocess.call(command)
		
def patch_instance():
	instance_path = os.path.join(instance_root, recipe_dict['DIRECTORY'])
	command = os.path.join(instance_path, 'patch.qmake.paths.bat')
	subprocess.call([command])
	
def register_instance():
	instance_path = os.path.join(instance_root, recipe_dict['DIRECTORY'])
	command = []
	#operation_runner
	command.append(os.path.join(symbian_tools_path, 'operationrunner.exe'))
	
	#QtCreator location within Nokia Qt SDK (/QtCreator automatically added)
	command.append("--sdktargetdir")
	command.append(qtsdk_path)
	
	#Operation to perform
	command.append('RegisterQtInCreatorV2')
	
	#Qt version label
	command.append(recipe_dict['LABEL'])
	
	#qmake path (/bin/qmake automatically added)
	command.append(instance_path)
	
	#instance path (EPOCROOT)
	command.append(instance_path)
	
	#sbs path
	sbs_path = ''
	if recipe_dict['SYMBIAN_VERSION'] != 'Symbian^1':
                sbs_path = os.path.join(symbian_tools_path, 'sbs', 'bin')

	command.append(sbs_path)
	
	print("Running operationrunner with parameters: ")
	print(command)
	
	subprocess.call(command)

if __name__ == '__main__':
	init()
	process_input()
	create_instance()
	patch_instance()
	register_instance()
