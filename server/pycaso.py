#!/usr/bin/env python

from core.logger import Logger
from core.config import Configuration
from core.server import TileServer
from core.token import TokenManager
from util.daemon import Daemon
from util.pid import write_pid

class Pycaso(Daemon):
	"""
	Application main class
	It has the responsibility to instantiate, initialize, and configure all
	the application services/modules
	"""
	def __init__(self):
		self.config = Configuration()
		self.server = TileServer()
		self.tm = TokenManager()
	
	def configure(self, cfgfile):
		self.config.load(cfgfile)
		
		Logger().configure(self.config.logger)
		self.server.configure(self.config.server)
		self.tm.configure(self.config)
		
		if self.config.general.daemon:
			Logger().info("Running as daemon")
			self.daemonize()
	
	def start(self):
		write_pid()
		self.server.start()
			
	def stop(self):
		self.server.stop()
		
if __name__ == '__main__':
	
	from constants.general import CONFIGURATION_FILE, HELP_FILE, VERSION
	import sys
	
	# Import Psyco if available
	try:
		import psyco
		psyco.full()
	except ImportError:
		pass

	# TODO: Extract argument parsing method
	cfgfile = CONFIGURATION_FILE
	
	# Parse params
	for i in range(len(sys.argv)):
		if sys.argv[i] == "-c":
			cfgfile = sys.argv[i+1]
		elif sys.argv[i] == "-h":
			print open(HELP_FILE).read()
			sys.exit()
		elif sys.argv[i] == "-v":
			print VERSION
			sys.exit()
	
	pycaso = Pycaso()
	pycaso.configure(cfgfile)
	pycaso.start()
