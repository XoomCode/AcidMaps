from constants.http.params import *
from constants.types import *
from constants.format import RGBA_BYTES, RGBA

from ctypes import Structure, c_int, c_char, POINTER

from core.gislib import gislib
from core.points import c_coord
from util.image import pnm2png

class c_box(Structure):
    _fields_ = ("top", c_int), ("left", c_int), ("bottom", c_int), ("right", c_int)

class c_config(Structure):
    _fields_ = ("coords", POINTER(c_coord)), ("size", c_int), ("bbox", c_box)

class TileRenderer():
	
	MAX_ALPHA = 255
	
	def __init__(self, params):
		self.params = params
	
	def render(self):
		# Set graphic type
		type = HEATMAP
		if self.params.has_key(TYPE):
			type = self.params[TYPE]

		if type == HEATMAP:
			return self.drawHeatmap()
		elif type == ISOLINE:
			return self.drawIsoline()
		elif type == VORONOI:
			return self.drawVoronoi()
   
	def buildConfig(self, resumed):
		config = c_config() 
		
		if resumed:
			config.coords = self.params[POINTS_RESUMED]
			config.size = len(self.params[POINTS_RESUMED])
		else: 
			config.coords = self.params[POINTS]
			config.size = len(self.params[POINTS])
		
		# Get BBOX
		bbox = c_box()
		bbox.top = int(self.params[TOP])
		bbox.left = int(self.params[LEFT])
		bbox.bottom = int(self.params[BOTTOM])
		bbox.right = int(self.params[RIGHT])
		config.bbox = bbox
		
		return config
		
	def drawHeatmap(self):
		# Parameters used
		width = int(self.params[RIGHT]) - int(self.params[LEFT])
		height = int(self.params[BOTTOM]) - int(self.params[TOP])
		diameter = int(self.params[DIAMETER])
		max_value= int(self.params[MAX_VALUE])
		
		# Space needed to store all the bytes
		bufferLength = width * height * RGBA_BYTES
		
		# Create the optimized buffer
		OptimizedBuffer = c_char * bufferLength
		buffer = OptimizedBuffer()
		
		alpha = self.MAX_ALPHA
		if (self.params.has_key(ALPHA)):
			alpha = int(self.params[ALPHA])
		
		gislib.heatmap(self.buildConfig(False), buffer, diameter, max_value, alpha)
		return pnm2png(RGBA, (width, height), buffer) 
	
	def drawIsoline(self):
		width = int(self.params[RIGHT]) - int(self.params[LEFT])
		height = int(self.params[BOTTOM]) - int(self.params[TOP])
		
		# Space needed to store all the bytes
		bufferLength = width * height * RGBA_BYTES
		
		# Create the optimized buffer
		OptimizedBuffer = c_char * bufferLength
		buffer = OptimizedBuffer()
		
		alpha = self.MAX_ALPHA
		if (self.params.has_key(ALPHA)):
			alpha = int(self.params[ALPHA])

		gislib.inverse_distance(self.buildConfig(True), buffer, self.params[INTERVALS], len(self.params[INTERVALS]), int(self.params[DIAMETER]), alpha)
				
		return pnm2png(RGBA, (width, height), buffer)
	
	def drawVoronoi(self):
		width = int(self.params[RIGHT]) - int(self.params[LEFT])
		height = int(self.params[BOTTOM]) - int(self.params[TOP])
		
		# Space needed to store all the bytes
		bufferLength = width * height * RGBA_BYTES
		
		# Create the optimized buffer
		OptimizedBuffer = c_char * bufferLength
		buffer = OptimizedBuffer()
		
		alpha = self.MAX_ALPHA
		if (self.params.has_key(ALPHA)):
			alpha = int(self.params[ALPHA])
		
		gislib.nearest_neigh(self.buildConfig(True), buffer, self.params[INTERVALS], len(self.params[INTERVALS]), int(self.params[DIAMETER]), alpha)
			
		return pnm2png(RGBA, (width, height), buffer)
