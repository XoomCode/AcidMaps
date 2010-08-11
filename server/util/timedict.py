from time import time

class TimeDict(dict):
	"""
	Garbage collected dictionary based on objects lifetime time
	"""
	def __init__(self, lifetime=0):
		"""
		Lifetime: in seconds, how much time the objects should live
		"""
		dict.__init__(self)
		self.lifetime = lifetime
	
	def __setitem__(self, key, value):
		"""
		Store the value, and update the object last access
		"""
		dict.__setitem__(self, key, [value, time()])
	
	def __getitem__(self, key):
		"""
		Update the object last access
		"""
		dict.__getitem__(self, key)[1] = time()
		return dict.__getitem__(self, key)[0]
	
	def get(self, key):
		if dict.__contains__(self, key):
			dict.__getitem__(self, key)[1] = time()
			return dict.get(self, key)[0]
		return None
	
	def clean(self):
		"""
		Removed expired elements
		"""
		t = time()
		for k, v in self.items():
			if t > v[1] + self.lifetime:
				del self[k]
