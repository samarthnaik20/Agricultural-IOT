
def split(message,k):
	#message = "rtedgvdfxgbfbhgcbhfgtfbhcgbhfghnfghfcghfvnbnvbnvgngvhfghfghf"
	a = len(message) 
	n = a/k
	l = n+1
	if(a < k):
		n = a
		l = 1


	m = ["0" for x in range(l)]

	for i in range(0,l):
		j = i+1
		if(j != n+1):
			m[i] = message[i*30:(j*30)-1]
		else:
			m[i] = message[i*30-1:]
	print m

	return m
