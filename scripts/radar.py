
import math
import Image, ImageDraw

im = Image.new ("RGBA", (256,256))

edge_radius = 16
line_col = 0x80ffffff

for i in range (edge_radius, 256-edge_radius):
	im.putpixel ((i,0), line_col)
	im.putpixel ((0,i), line_col)
	im.putpixel ((i,255), line_col)
	im.putpixel ((255,i), line_col)

for i in range (1, 255):
	im.putpixel ((i,128), line_col if (i/4)%2 else 0)
	im.putpixel ((128,i), line_col if (i/4)%2 else 0)

for x in range (0, edge_radius+1):
	for y in range (0, edge_radius+1):
		if int (math.sqrt (x*x + y*y)) == edge_radius:
			im.putpixel ((edge_radius-x,edge_radius-y), line_col)
			im.putpixel ((x+255-edge_radius,edge_radius-y), line_col)
			im.putpixel ((edge_radius-x,y+255-edge_radius), line_col)
			im.putpixel ((x+255-edge_radius,y+255-edge_radius), line_col)
			
im.save ("res/radar.png")
