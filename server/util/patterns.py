class Singleton(object):
	"""
	Abstract class.
	It ensures that there will be only one instance of a certain class
	Just use this class as the parent.
	"""
	def __new__(cls, *p, **k):
		if not '_the_instance' in cls.__dict__:
				cls._the_instance = object.__new__(cls, *p, **k)
		return cls._the_instance
	
class Monostate(object):
	"""
	Abstract class
	Allows multiple instances of the same class, to share the same internal state
	Just use this class as the parent.
	"""
	_state = {}
	def __new__(cls, *p, **k):
		self = object.__new__(cls, *p, **k)
		self.__dict__ = cls._state
		return self

class DynamicObject:
	"""
	A plain object, that can be extended on runtime
	"""
	pass
