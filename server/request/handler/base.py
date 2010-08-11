class BaseHandler():
	"""
	Abstract request handler
	"""

	def set_next(self, next):
		"""
		Define which class is the next in the command chain
		"""
		self.next = next
		return next
	
	def handle(self, request):
		"""
		Method prototype
		Should be implemented in inheriting classes
		"""
		try:
			self.next.handle(request)
		except AttributeError:
			pass
