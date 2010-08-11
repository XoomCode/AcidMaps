from ctypes import CDLL
import platform

from constants.platform import DARWIN, LINUX, WINDOWS, LIN_LIB, MAC_LIB, WIN_LIB

system_name = platform.system().lower()
if LINUX in system_name:
	gislib = CDLL(LIN_LIB)	
elif DARWIN in system_name:
	gislib = CDLL(MAC_LIB)	
elif WINDOWS in system_name:
	gislib = CDLL(WIN_LIB)	
