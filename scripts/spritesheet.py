#!/usr/bin/python2

import sys
import os
from PIL import Image

# check arguments
if len(sys.argv) != 3:
	print "usage: script <input-dir> <output-filename>"
	sys.exit (-1)

inputDir, outputFilename = sys.argv[1:]

outIm = Image.new ("RGBA", (512, 512))
i = 0
for node in sorted (os.listdir (inputDir)):
	im = Image.open (inputDir+"/"+node)
	outIm.paste (im, ((i%8)*64, (i//8)*64) )
	i += 1

outIm.save (outputFilename)

