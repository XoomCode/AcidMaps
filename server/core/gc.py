from threading import Thread
from time import sleep

class GC(Thread):
	"""
	This class represents a garbage collector that will run with a given frequency
	"""
	def __init__(self, frequency):  
		Thread.__init__(self)
		self.collectables = []
		self.frequency = frequency
		self.running = True
	
	def add(self, collectable):
		"""
		Adds a new garbage collectable object
		"""
		self.collectables.append(collectable)
	
	def remove(self, collectable):
		"""
		Removes the collectable from the collection
		"""
		self.collectables.remove(collectable)
	
	def stop(self):
		self.running = False
			
	def run(self):
		while self.running:
			sleep(self.frequency)
			for collectable in self.collectables:
				collectable.clean()
