from base import BaseHandler

from core.config import Configuration
from core.tile import TileRenderer

from constants.http.status import INTERNAL_SERVER_ERROR
from constants.http.params import LEFT, BOTTOM, RIGHT, TOP

class TileHandler(BaseHandler):
	
	def handle(self, request):
		"""
		This handler generates the tile and 
		set it into the context
		"""
		max_tile_size = Configuration().general.maxTileSize
		width, height = self.tile_size(request.params)
		
		if width < 0 or height < 0 or width > max_tile_size or height > max_tile_size:
			self.send_response(INTERNAL_SERVER_ERROR)
			self.end_headers()
			
		else:
			tileRenderer = TileRenderer(request.params)
			request.response = tileRenderer.render()
			try:
				self.next.handle(request)
			except AttributeError:
				pass
		
	def tile_size(self, params):
		width = int(params[RIGHT]) - int(params[LEFT])
		height = int(params[BOTTOM]) - int(params[TOP])
		return width , height