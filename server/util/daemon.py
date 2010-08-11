#  Daemon Module - basic facilities for becoming a daemon process
#  By Coy Krill
#  Combines ideas from Steinar Knutsens daemonize.py and
#  Jeff Kunces demonize.py

"""Facilities for Creating Python Daemons"""

import os
import time
import sys

class NullDevice:
	def write(self, s):
		pass

class Daemon:
	def daemonize(self):
		if (not os.fork()):
			# get our own session and fixup std[in,out,err]
			os.setsid()
			sys.stdin.close()
			sys.stdout = NullDevice()
			sys.stderr = NullDevice()
			if (not os.fork()):
				# hang around till adopted by init
				ppid = os.getppid()
				while (ppid != 1):
					time.sleep(0.5)
					ppid = os.getppid()
			else:
				# time for child to die
				os._exit(0)
		else:
			# wait for child to die and then bail
			os.wait()
			sys.exit()
