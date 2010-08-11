from util.patterns import Singleton
from util.gcdict import TimeDict

from core.gc import GC 

class TokenManager(Singleton):
	
	def configure(self, cfg):
		TokenManager._dict = TimeDict(cfg.gc.lifetime)
		
		# Launch the garbage collector
		TokenManager.gc = GC(cfg.gc.frequency)
		TokenManager.gc.add(TokenManager._dict)
		TokenManager.gc.start()
	
	def set(self, key, value):
		TokenManager._dict[key] = value
	
	def get(self, key):
		return TokenManager._dict[key]

	def unset(self, key):
		if TokenManager._dict.has_key(key):
			del TokenManager._dict[key]

	def has(self, key):
		return TokenManager._dict.has_key(key)
