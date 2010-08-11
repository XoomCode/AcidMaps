from base import BaseHandler

from constants.http.params import TOKEN
from core.token import TokenManager

class TokenHandler(BaseHandler):
	
	def handle(self, request):
		"""
		Verifies that the parameters has contains a valid token
		and merges the parameters with the one stored in the 
		token manager
		"""
		token = request.params.get(TOKEN)
		if token and TokenManager().has(token):
			stored_params = TokenManager().get(token)
			request.params.merge(stored_params)
			try:
				self.next.handle(request)
			except AttributeError:
				pass
