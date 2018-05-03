pathes = [
	[0, 10, 0, 30, 100],
	[10, 0, 50, 0, 0],
	[0, 50, 0, 20, 10],
	[30, 0, 20, 0, 60],
	[100, 0, 10, 60, 0]
	]

road = [[0 for i in range (5)] for j in range (5)]

for i in range (0, 5):
	road[i] = [[1 if pathes[j] != 0 else 0] for j in range(5)]

for row in road:
	row.remove('0')
for row in pathes:
	row.sort()



#for i in range (1, 6):
#	for j in range (6 - i):
		
