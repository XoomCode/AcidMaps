from ConfigParser import SafeConfigParser 
from util.patterns import DynamicObject, Monostate

class Configuration(Monostate):
	"""
	This class manages all the configuration
	It has the responsibility to read and save configuration files
	"""
	def load(self, filename):
		"""
		Parse file to retrieve properties
		"""
		parser = SafeConfigParser()
		parser.read(filename)
		
		self.general = DynamicObject()
		self.general.daemon = parser.getboolean("General", "Daemon")
		self.general.crossdomain = parser.get("General", "Crossdomain")
		self.general.maxTileSize = parser.get("General", "MaxTileSize")

		self.server = DynamicObject()
		self.server.host = parser.get("Server", "Host")
		self.server.port = parser.getint("Server", "Port")
		
		self.logger = DynamicObject()
		self.logger.logFile = parser.get("Logger", "LogFile")
		self.logger.failsafeLogFile = parser.get("Logger", "FailsafeLogFile")
		self.logger.logMaxLenght = parser.getint("Logger", "LogMaxLenght")
		self.logger.smtpHost = parser.get("Logger", "SMTPHost")
		self.logger.emailSender = parser.get("Logger", "EmailSender")
		self.logger.emailReceivers = parser.get("Logger", "EmailReceivers")
		self.logger.fileLogLevel = parser.get("Logger", "FileLogLevel")
		self.logger.smtpLogLevel = parser.get("Logger", "SMTPLogLevel")
		
		self.gc = DynamicObject()
		self.gc.frequency = parser.getint("GC", "Frequency")
		self.gc.lifetime = parser.getint("GC", "Lifetime")

	def write(self, filename):
		"""
		Write properties to file
		"""
		parser = SafeConfigParser()
		
		if not parser.has_section("General"):
			parser.add_section("General")
		parser.set("General", "Daemon", str(self.general.daemon))

		if not parser.has_section("Server"):
			parser.add_section("Server")
		parser.set("Server", "Host", str(self.server.host))
		parser.set("Server", "Port", str(self.server.port))
		
		if not parser.has_section("Logger"):
			parser.add_section("Logger")
		parser.set("Logger", "LogFile", str(self.logger.logFile))
		parser.set("Logger", "FailsafeLogFile", str(self.logger.failsafeLogFile))
		parser.set("Logger", "LogMaxLenght", str(self.logger.logMaxLenght))
		parser.set("Logger", "SMTPHost", str(self.logger.smtpHost))
		parser.set("Logger", "EmailSender", str(self.logger.emailSender))
		parser.set("Logger", "EmailReceivers", str(self.logger.emailReceivers))
		parser.set("Logger", "FileLogLevel", str(self.logger.fileLogLevel))
		parser.set("Logger", "SMTPLogLevel", str(self.logger.smtpLogLevel))
		
		if not parser.has_section("GC"):
			parser.add_section("GC")
		parser.set("GC", "Frequency", str(self.gc.frequency))
		parser.set("GC", "Lifetime", str(self.gc.lifetime))
		
		parser.write(open(filename, "w"))