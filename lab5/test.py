import subprocess

for i in range(1000, 15001, 2000):
	r = subprocess.run(['./e', str(i), str(i)], stdout=subprocess.PIPE).stdout.decode('utf-8')
	print(r)