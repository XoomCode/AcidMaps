from BaseHTTPServer import BaseHTTPRequestHandler

from constants.http.params import *
from constants.http.head import CONTENT_LENGTH
from constants.actions import PUSH, POP
from constants.error import UNEXPECTED_ERROR

from util.paramsdict import ParamsDict

from core.logger import Logger
from core.token import TokenManager
from core.points import PointsList
from core.intervals import IntervalsList

from request.handler.crossdomain import CrossdomainHandler
from request.handler.params import ParamsHandler
from request.handler.token import TokenHandler
from request.handler.tile import TileHandler
from request.handler.response import ResponseHandler

class PycasoRequestHandler(BaseHTTPRequestHandler):
	
	# This should be configured in the config.ini
	MAX_TILE_SIZE = 1024
	HEATMAP_FACTOR = 100
	
	def do_GET(self):
		handler = CrossdomainHandler()
		next_handler = handler.set_next(ParamsHandler())
		next_handler = next_handler.set_next(TokenHandler())
		next_handler = next_handler.set_next(TileHandler())
		next_handler = next_handler.set_next(ResponseHandler())
		handler.handle(self) 
	
	def do_POST(self):
		
		# Get post data
		content_length = int(self.headers[CONTENT_LENGTH])
		post = self.rfile.read(content_length)
		
		# Parse the parameter
		params = ParamsDict()
		params.parse(post)
		
		# Generate token
		token = params.hash()
		
		# Check if action is defined
		action = PUSH
		if params.has_key(ACTION):
			Logger().info("POST Action: %s" % ACTION)
			action = params[ACTION]
			params.pop(ACTION, None)
		
		# Store values
		if action == PUSH:
			self._push(token, params)
		
		# Clean 
		elif action == POP:
			self._pop(token)
		
		# Send headers
		self.send_response(200)
		self.end_headers()
		
		self.wfile.write(token)
	
	def do_DELETE(self):
		try:
			# Get post data
			content_length = int(self.headers[CONTENT_LENGTH])
			post = self.rfile.read(content_length)
			
			# Parse the parameter
			params = ParamsDict()
			params.parse(post)
			
			# Generate token
			token = params.hash()
			self._pop(token)
			
			# Send headers
			self.send_response(200)
			self.end_headers()
		except:
			Logger().error(UNEXPECTED_ERROR)
	
	def _push(self, token, params):
		if (params.has_key(INTERVALS)):
			intervals = IntervalsList()
			intervals.parse(params[INTERVALS])
			params[INTERVALS] = intervals.array
        
		pointsAsStr = params[POINTS];
		
		points = PointsList()
		
		points.parse(pointsAsStr)
		params[POINTS] = points.array
        
		if (params.has_key(CELLS)):
			cell_with_more_points = points.parseAndResume(pointsAsStr, int(params[CELLS]))
		else:
			cell_with_more_points = points.parseAndResume(pointsAsStr)

		if not params.has_key(MAX_VALUE):
			params[MAX_VALUE] = len(cell_with_more_points) * self.HEATMAP_FACTOR * 0.95
		params[POINTS_RESUMED] = points.array
		
		TokenManager().set(token, params)
	
	def _pop(self, token):
		if TokenManager().has(token):
			TokenManager().unset(token)
