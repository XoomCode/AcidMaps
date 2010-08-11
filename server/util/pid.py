from constants.general import PID_FILE
from core.logger import Logger

import os
import platform

def write_pid():
	system_name = platform.system().lower()

	if "linux" in system_name:
		try:
			pid_file = open(PID_FILE, "w")
			pid_file.write(str(os.getpid()))
			pid_file.close()
		except:
			Logger().warning("PID couldn't be written")
