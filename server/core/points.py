from ctypes import Structure, c_int, c_float
import sys

class c_coord(Structure):
    _fields_ = ("x", c_int), ("y", c_int), ("accum", c_int), ("avg", c_int), ("most_freq", c_int), ("max", c_int) , ("distance", c_float)

class PointsList():
	CELL_SIZE_LIMIT = 64 # to avoid having cell size of 256 (tile size) that would obviously miss information 
	DEFAULT_CELLS = 64
	
	def parse(self, str):
		splitted = str.split(';') 
		
		OptimizedArray = c_coord * len(splitted)
		self.array = OptimizedArray()

		for i in xrange(len(splitted)):
			point = splitted[i]
			if point:
				parts = point.split(',') 
				c = self.array[i]
				c.x = int(float(parts[0]))
				c.y = int(float(parts[1]))
				c.accum = int(float(parts[2])) 
				c.max = int(float(parts[2]))
				c.avg = int(float(parts[2])) 
				c.distance = 0.0
	
	def parseAndResume(self, str, cells = DEFAULT_CELLS):
		max_x = -sys.maxint
		max_y = -sys.maxint

		min_x = sys.maxint
		min_y = sys.maxint
		
		points = []
		splitted = str.split(';')
		for i in xrange(len(splitted)):
			point = splitted[i]
			if point:
				parts = point.split(',') 
				c = c_coord()
				c.x = int(float(parts[0]))
				c.y = int(float(parts[1]))
				c.max = int(float(parts[2])) # max will be used as the reference
				c.distance = 0.0

				points.append(c)

				if (c.x < min_x):
					min_x = c.x
				if (c.x > max_x):
					max_x = c.x
				if (c.y < min_y):
					min_y = c.y
				if (c.y > max_y):
					max_y = c.y

		cand_cell_size = max(((max_x - min_x)/cells), ((max_y - min_y)/cells))

		pot = 3 # guarantee that min cell size is 8
		while True:
			if cand_cell_size < 2**pot:
				cell_size = 2**pot
				break
			else:
				pot += 1 
        
		if cell_size > self.CELL_SIZE_LIMIT:
			cell_size = self.CELL_SIZE_LIMIT

		resumed = {}
		for p in points:
			key = "%s" % (p.x/cell_size) + "-" + "%s" % (p.y/cell_size)
			if not resumed.has_key(key):
				resumed[key] = [p]
			else:
				resumed[key].append(p)

		OptimizedArray = c_coord * len(resumed.keys())
		self.array = OptimizedArray()

		i = 0
		cell_with_more_points = []
		for key in resumed.keys():
			p = self.array[i]
			p.avg = 0
			p.max = 0
			p.accum = 0
			p.x = 0
			p.y = 0
			
			if len(resumed[key]) > len(cell_with_more_points):
				cell_with_more_points = resumed[key]
			
			freq = {}	
			for point in resumed[key]:
				p.accum += point.max
				p.avg += point.max
				p.max = max(point.max, p.max)
				p.x += point.x
				p.y += point.y
				
				if freq.has_key(point.max):
					freq[point.max] += 1
				else:
					freq[point.max] = 1					
            
			most_frequent = 0
			most_frequent_freq = 0
			for k, v in freq.iteritems():
				if v > most_frequent_freq:
					most_frequent_freq = v
					most_frequent = k

			n = len(resumed[key])
			p.x /= n
			p.y /= n 
			p.avg /= n
			p.most_freq = most_frequent

			i += 1

		return cell_with_more_points
