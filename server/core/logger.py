import logging
from logging.handlers import SMTPHandler, RotatingFileHandler

from util.patterns import Singleton
from util.util import system_log

from constants.general import APPLICATION_NAME

class Logger(Singleton):
	"""
	
	"""
	
	def configure(self, cfg):
		"""
		Configures the Logger module
		"""
		
		self.configured = False
		
		self.log = logging.getLogger(APPLICATION_NAME)
		formatter = logging.Formatter("%(asctime)s [%(levelname)s]: %(message)s")
		
		# File logger
		try:
			fileLogLevel = cfg.fileLogLevel.lower()
			if not fileLogLevel == "none":
				try:
					fileHandler = RotatingFileHandler(cfg.logFile, 'a', cfg.logMaxLenght)
				except:
					fileHandler = RotatingFileHandler(cfg.failsafeLogFile, 'a', cfg.logMaxLenght)
				fileHandler.setFormatter(formatter)
				fileHandler.setLevel(logLevel(fileLogLevel))
				
				self.log.addHandler(fileHandler)
		
		except Exception:
			system_log("File logger configuration failed")
		
		# SMTP logger
		try:
			smtpLogLevel = cfg.smtpLogLevel.lower()
			if not smtpLogLevel == "none":
				subject_str = APPLICATION_NAME + ' error log'
				smtpHandler = SMTPHandler(cfg.smtpHost, cfg.emailSender, cfg.emailReceivers, subject_str)
				smtpHandler.setFormatter(formatter)
				smtpHandler.setLevel(logLevel(smtpLogLevel))
				
				self.log.addHandler(smtpHandler)
		
		except Exception:
			system_log("SMTP Logger configuration failed")
		
		self.log.setLevel(logging.DEBUG)
		self.configured = True
		
		self.info("Logger configured")
	
	def debug(self, text):
		"""
		Log a debug message
		"""
		if self.configured:
			self.log.debug(text)
	
	def info(self, text):
		"""
		Log an info message
		"""
		if self.configured:
			self.log.info(text)
	
	def warning(self, text):
		"""
		Log a warning message
		"""
		if self.configured:
			self.log.warning(text)
	
	def error(self, text):
		"""
		Log an error message
		"""
		if self.configured:
			self.log.error(text)
	
	def critical(self, text):
		"""
		Log a critical message
		"""
		if self.configured:
			self.log.critical(text)


def logLevel(level_str):
	level = logging.NOTSET
	
	level_str = level_str.lower()
	if level_str == "debug":
		level = logging.DEBUG
	elif level_str == "info":
		level = logging.INFO
	elif level_str == "warning":
		level = logging.WARNING
	elif level_str == "error":
		level = logging.ERROR
	elif level_str == "critical":
		level = logging.CRITICAL
	return level
