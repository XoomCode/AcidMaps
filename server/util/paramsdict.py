from hashlib import md5
from urllib import unquote

from constants.http.params import QUERY_MARK

class ParamsDict(dict):
	"""
	Class used to manage parameters passed from POST and GET requests
	It also, allows to calculate a unique hash for the dictionary, 
	base on the values of the items stored
	"""
	def parse(self, str):
		"""
		Read parameters from different requests
		"""
		# Unquote string
		str = unquote(str)
		
		# Read param string from a GET request 
		query_mark_pos = str.find(QUERY_MARK)
		if query_mark_pos > -1:
			str = str[query_mark_pos + 1:]
		
		# Set values into the dictionary
		for kv in str.split("&"):
			pos = kv.index('=')
			self[kv[:pos]] = kv[pos + 1:]
	
	def hash(self):
		"""
		It also, allows to calculate a unique hash for the dictionary, 
		base on the values of the items stored
		"""
		values = self.values()
		values.sort()
		aux = ""
		for value in values:
			aux += value
		return md5(aux).hexdigest()
	
	def merge(self, d):
		for k in d:
			if k not in self:
				self[k] = d[k]
		return self
	
	def __str__(self):
		items = []
		iteritems = self.items()
		iteritems.sort()
		for item in iteritems:
			items.append("=".join(item))
		return "&".join(items)
