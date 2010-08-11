from base import BaseHandler
from core.params import ParamsDict

class ParamsHandler(BaseHandler):
	
	def handle(self, request):
		"""
		This handler parses the parameters and add
		them to the request
		"""
		request.params = ParamsDict()
		request.params.parse(request.path)
		
		try:
			self.next.handle(request)
		except AttributeError:
			pass
