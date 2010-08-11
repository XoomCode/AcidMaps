from request.handler.base import BaseHandler
from core.config import Configuration
from os.path import exists as path_exists

from constants.http.status import OK, NOT_FOUND
from constants.http.head import CONTENT_TYPE
from constants.http.mime import MIMETYPE_XML
from constants.general import CROSSDOMAIN_XML

from util.util import read_file

class CrossdomainHandler(BaseHandler):
	
	def handle(self, request):
		"""
		Check if there is client is asking for a 
		crossdomain.xml file, open it, and return it
		If not, pass the request to the next handler
		"""
		
		if CROSSDOMAIN_XML in request.path:
			if path_exists(Configuration().general.crossdomain):
				request.send_response(OK)
				request.send_header(CONTENT_TYPE, MIMETYPE_XML)
				request.end_headers()
				request.wfile.write(read_file(Configuration().general.crossdomain))
			else:
				request.send_response(NOT_FOUND)
				request.end_headers()
				
		else:
			try:
				self.next.handle(request)
			except AttributeError:
				pass
