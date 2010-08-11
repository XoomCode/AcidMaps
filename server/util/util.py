def str_to_bool(str):
	"""Converts a boolean string into a real boolean value"""
	return (str.lower().strip() == "true")

def system_log(text):
	"""Logs into a special file whenever the logger it's not available"""
	file = open('system.log', 'a+')
	line = "Systemlog: " + text + "\n"
	file.write(line)
	file.close()

def read_file(filename):
	try:
		file = open(filename)
		bytes = file.read()
	except:
		bytes = []
	finally:
		file.close()
	return bytes 