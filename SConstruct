import os, sys, string, time
from ColorPrint import *
from BuildInfo import *

# scons options:
#    implicit_cache: Cache implicit dependencies, like *.d files
SetOption('implicit_cache', 1)

#-----------------------------------------------------------------------------------------------------------------------
# top root
#-----------------------------------------------------------------------------------------------------------------------
def backtrack(str):
	tops = ( '.', '/' )
	cldir=os.getcwd()

	while cldir not in tops:
		if os.path.exists(os.path.join(cldir, str)):
			break
		cldir=os.path.dirname(cldir)
	return cldir

#-----------------------------------------------------------------------------------------------------------------------
# Recusive get all directories in folder, and excludes some folders and files by theirs name
#-----------------------------------------------------------------------------------------------------------------------
def RecusiveGetDirs(self, abs_path_dir, exclude_folders = []):
    glob_folders = []
    lst = [ name for name in os.listdir(abs_path_dir) if os.path.isdir(os.path.join(abs_path_dir, name)) and name[0] != '.' and exclude_folders.count(name) == 0 ]
    lst.sort()
    # resuive get folder
    for dir in lst:
        sub_dir = os.path.join(abs_path_dir, dir)
        glob_folders.append(sub_dir)
        glob_folders += RecusiveGetDirs(self, sub_dir, exclude_folders)
    return glob_folders

#-----------------------------------------------------------------------------------------------------------------------
# Recusive get all files in folder, and excludes some folders and files by theirs name
#-----------------------------------------------------------------------------------------------------------------------
def RecusiveGlobFiles(self, abs_path_dir, glob_list, exclude_folders = [], exclude_files = []):
    glob_files = []
    lst = [ name for name in os.listdir(abs_path_dir) if os.path.isdir(os.path.join(abs_path_dir, name)) and name[0] != '.' and exclude_folders.count(name) == 0 ]
    lst.sort()
    # get all files in current folder
    for glob in glob_list:
        globstr = os.path.join(abs_path_dir, glob)
        folder_files = Glob(globstr)
        # exclude files from exclude file list
        file_list = [ name for name in folder_files if os.path.isdir(name.abspath) == False and exclude_files.count(name.name) == 0 ]
        # add files to file list
        glob_files += file_list
    # recusive get files in sub folder
    for dir in lst:
        sub_dir = os.path.join(abs_path_dir, dir)
        glob_files += RecusiveGlobFiles(self, sub_dir, glob_list, exclude_folders, exclude_files)
    return glob_files

# Initialize
topdir = os.getcwd()
output_root_dir = os.path.join(topdir, 'output')
output_bin_dir = os.path.join(output_root_dir, 'bin')
output_libs_dir = os.path.join(output_root_dir, 'libs')
vendor_dir = os.path.join(topdir, 'vendors')

print "topdir: " + topdir

def DisplayBuildStatus():
    status, failures_message = build_status()
    if status == 'failed':
        ColorPrint(failures_message, 0, nFore_Red, nBack_DefaultBack);
    elif status == 'ok':
        ColorPrint('Build Success!', 0, nFore_Green, nBack_DefaultBack);
atexit.register(DisplayBuildStatus)

AddMethod(Environment, RecusiveGetDirs)
AddMethod(Environment, RecusiveGlobFiles)

# flags
cc_flags = ['-Wall', '-fno-strict-aliasing', '-Werror', '-std=gnu++11']  # for c and c++, it will be added to CCFLAGS
c_flags = []   # for c, it will be added to CFLAGS
cxx_flags = [] # for c++, it will be added to CXXFLAGS
link_flags = ['-static', '-m64']
config = {
    'build': '',     # 'debug' or 'release'
}

# Read the optimization mode
if ARGUMENTS.has_key('opt'):
    cc_flags.append('-O'+ARGUMENTS.get('opt'))
    if ARGUMENTS.get('opt') != '0':
        config['build'] = 'release'
    else:
        config['build'] = 'debug'
else:
    cc_flags.append('-O0')
    cc_flags.append('-D_DEBUG_')
    config['build'] = 'debug'

if config['build'] == 'debug':
    cc_flags.append('-g3')
else:
    cc_flags.append('-g0')

# Environments
env = Environment(Env = os.environ)
env['topdir'] = topdir
env['output_root'] = output_root_dir
env['output_libs'] = output_libs_dir
env['output_bin'] = output_bin_dir
env['config'] = config

env['CCFLAGS'] = cc_flags
env['CFLAGS'] = c_flags
env['CXXFLAGS'] = cxx_flags
env['LINKFLAGS'] = link_flags

env['main_depends'] = []

env['CPPPATH'] = [
    '.',
    '#',
    '#/vendors/xerces/src',
    '#/framework/src',
    '#/xmlwrapper/src',
]

env['LIBPATH'] = [
    env['output_libs'],
]

env['lib_list'] = [
    'xmlwrapper',
    'framework',
    'xerces',
    'pthread',
    'dl',
]

scons_list = [
    'xml',
    'vendors',
    'xmlwrapper/src',
    'framework/src',
    'main/src'
]

for scons_dir in scons_list:
    print '\n'
    output_dir = os.path.join(output_root_dir, scons_dir)
    script = os.path.join(output_dir, 'SConscript')
    
    print 'scons_dir : ' + scons_dir
    print 'output_dir : ' + output_dir
    print 'script : ' + script

    config = {}
    config['output_libs'] = output_libs_dir
    config['output_bin'] = output_bin_dir
    print "config['output_libs']   = "  +  config['output_libs']
    print "config['output_bin']   = "  +  config['output_bin']

    #export 
    Export('env config')
    VariantDir(output_dir, scons_dir, duplicate=0)
    SConscript(script)


