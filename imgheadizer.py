
from PIL import Image

im = Image.open('img.png') # Can be many different formats.
pix = im.load()
x = 0 
y = 0
for y in range(16):
	for x in range(16):
		print ','.join(map(str, pix[x,y])),  # Get the RGBA Value of the a pixel of an image
		print ",",
