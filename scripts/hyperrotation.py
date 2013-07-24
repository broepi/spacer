
import Image

def hyperrotate (inputlist, outfilename):
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


inputlist1 = []
for i in range (64):
	im = Image.open ("prerendered/spaceship/%04d.png" % i)
	inputlist1.append (im)
hyperrotate (inputlist1, "res/spaceship-hyperrotation.png")

inputlist2 = []
for i in range (32,64):
	im = Image.open ("prerendered/spaceship/%04d.png" % i)
	inputlist2.append (im)
hyperrotate (inputlist2, "res/spaceship-hyperrotation-2.png")
