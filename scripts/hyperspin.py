#!/usr/bin/python2

import sys
from PIL import Image

def hyperspin (inputlist, outfilename):
	countmatrix = []
	for y in range (64):
		row = []
		for x in range (64):
			count = 0
			for i in range (32):
				if inputlist[i].getpixel((x,y))[3] > 0:
					count += 1
			row.append (count)
		countmatrix.append (row)
	outputimg = Image.new ("RGBA", (64,64))
	for y in range (64):
		for x in range (64):
			outpix = [0,0,0,0]
			for i in range (32):
				if countmatrix[y][x] > 0:
					inpix = inputlist[i].getpixel((x,y))
					outpix[0] += inpix[0] / float (countmatrix[y][x])
					outpix[1] += inpix[1] / float (countmatrix[y][x])
					outpix[2] += inpix[2] / float (countmatrix[y][x])
					outpix[3] += inpix[3] / 32.0
			outpix = map (lambda x: int(x), outpix)
			outpix [3] = max (1, outpix [3] * 2);
			outputimg.putpixel ((x,y), tuple(outpix))
	outputimg.save (outfilename)


# check arguments
if len(sys.argv) != 5:
	print "usage: script <input-dir> <output-filename> <start-frame> "+\
		"<frame-count>"
	sys.exit (-1)

inputDir, outputFilename, startFrame, frameCount = sys.argv[1:]
startFrame = int (startFrame)
frameCount = int (frameCount)

inputlist = []
for i in range (startFrame, startFrame+frameCount):
	im = Image.open (inputDir+"/%04d.png" % i)
	inputlist.append (im)
hyperspin (inputlist, outputFilename)
