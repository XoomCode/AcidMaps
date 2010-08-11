import Image
import StringIO

from constants.format import RAW, PNG

def pnm2png(mode, size, buffer):
	"""
	Convert raw image into png
	"""
	raw_file = Image.fromstring(mode, size, buffer, RAW, mode, 0, -1)
	
	png_file = StringIO.StringIO()
	raw_file.save(png_file, format = PNG)
	
	return png_file.getvalue()
