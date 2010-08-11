from ctypes import Structure, c_int, c_ubyte

class c_interv(Structure):
	_fields_ = ("up_to", c_int) , ("r", c_ubyte), ("g", c_ubyte), ("b", c_ubyte)

class IntervalsList():
	def parse(self, str):
		intervs = str.split(';')
		intervs_length = len(intervs)
		
		OptimizedArray = c_interv * intervs_length
		self.array = OptimizedArray()
		
		for i in xrange(intervs_length):
			interv = intervs[i]
			if interv:
				aux_arr = interv.split(',')
				
				if len(aux_arr) == 4:
					interv = self.array[i]
					interv.up_to = int(aux_arr[0])
					interv.r = int(aux_arr[1])
					interv.g = int(aux_arr[2])
					interv.b = int(aux_arr[3])
