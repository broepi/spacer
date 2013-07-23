
import Image
inputlist = []
for i in range (64):
	im = Image.open ("blender/rendered/spaceship/%04d.png" % i)
	inputlist.append (im)
outputimg = Image.new ("RGBA", (64,64))
for y in range (64):
	for x in range (64):
		outpix = [0,0,0,0]
		for i in range (64):
			outpix = map (lambda c: c[0]+c[1]/64.0, zip(outpix, inputlist[i].getpixel((x,y)) ))
		outpix = map (lambda x: int(x), outpix)
		outpix [3] = max (1, outpix [3] * 2);
		outputimg.putpixel ((x,y), tuple(outpix))
outputimg.save ("ex.png")

