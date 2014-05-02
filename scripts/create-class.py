#!/usr/bin/python2

import os
import os.path
import sys

srcDir = "src"
buildDir = "build"

# check arguments
if len(sys.argv) != 3:
	print "usage: script [<dir>/]<classname> [<dir>/]<superclass>"
	sys.exit (-1)

classPath, superPath = sys.argv[1:]

classPath = classPath.split ("/")
className = classPath [-1]
classNameL = className.lower ()
classNameU = className.upper ()
cPath = "/".join ([srcDir]+classPath[:-1])+"/"+classNameL+".cpp"
hPath = "/".join ([srcDir]+classPath[:-1])+"/"+classNameL+".h"
include = classNameL+".h"
guardName = classNameU+"_H"

superPath = superPath.split ("/")
superName = superPath [-1]
superNameL = superName.lower ()
includeSuper = "/".join (superPath[:-1]+[superNameL])+".h"

# create source file

fs = open (hPath, "w")
fs.write ("""
#ifndef """+guardName+"""
#define """+guardName+"""
"""+("\n#include \""+includeSuper+"\"\n" if superName!="" else "")+"""
class """+className+(" : public "+superName if superName!="" else "")+"""
{
public:
	"""+className+""" ();
	~"""+className+""" ();
};

#endif

""")
fs.close ()

# create header file

fs = open (cPath, "w")
fs.write ("""
#include \""""+include+"""\"

"""+className+"::"+className+""" ()
{
}

"""+className+"::~"+className+""" ()
{
}

""")
fs.close ()

