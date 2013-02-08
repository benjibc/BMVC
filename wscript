import Options
from os import unlink, symlink, popen
from os.path import exists

srcdir = "."
blddir = "build"
VERSION = "0.0.1"

def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")

def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.target = "bhmvc"
  obj.source = "bhmvc.cpp"
  obj.cxxflags = ["-D_FILE_OFFSET_BITS=64", "-D_LARGEFILE_SOURCE", "-std=c++11", "-O2" , "-I./bmvc/boost_file"]

def shutdown():
  if Options.commands['clean']:
    if exists('bhmvc.node'): unlink('bhmvc.node')
  else:
    if exists('build/Release/bhmvc.node') and not exists('bhmvc.node'):
      symlink('build/Release/bhmvc.node', 'bhmvc.node')

