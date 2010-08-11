from SocketServer import ThreadingTCPServer
from request.handler.pycasso import PycassoRequestHandler
from logger import Logger

class TileServer():
	"""
	This class has the responsibility to listen and answer requests done by
	different clients
	"""	
	def configure(self, cfg):
		Logger().info("Configuring Server")
		self.host = cfg.host
		self.port = cfg.port
		Logger().info("Server configured")
		
	def start(self):
		"""Start cache and administration services"""
		server_address = (self.host, self.port)
		Logger().info("Starting server on %s:%s" % server_address)
		self.server_instance = ThreadingTCPServer(server_address, PycassoRequestHandler)
		self.server_instance.serve_forever()
	
	def stop(self):
		"""Stop running services"""
		if self.server_instance:
			self.server_instance.server_close()
			Logger().info("Stopping server")
