from base import BaseHandler

from constants.http.status import OK

class ResponseHandler(BaseHandler):

	def handle(self, request):
		"""
		This handler parses the parameters and add
		them to the request
		"""
		try:
			# Send headers
			request.send_response(OK)
			request.end_headers()
			
			# Send the generated tile
			request.wfile.write(request.response)
			try:
				self.next.handle(request)
			except AttributeError:
				pass
		except:
			# Something went wrong
			# Log this
			pass
