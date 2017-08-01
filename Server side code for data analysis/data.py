#with time h1 = 6 , without time h1 = 7;

import urllib2


def callserver(with_time,time):


	try:
		#with_time = 1;                           # 0 for full table data, 1 for data of a particular time
		#time = "1-6-2017-11" ;                   # time of the data needed




		if(with_time == 1):
			h1 = 7;
			url = "https://kumarnikhil1198.000webhostapp.com/gettable.php?time=" + time ;

		else:
			h1 = 8;
			url = "https://kumarnikhil1198.000webhostapp.com/getfulltable.php";
		

		content = urllib2.urlopen(url).read()
		#print content

		mesharray = content.split(',')
		
		#print mesharray

		row_info = mesharray[0];

		if(len(mesharray) > 1):

			w1 = (len(mesharray) - 1)/h1;                                       # change here
			
			w, h = h1, w1;                                                      # change here
			data = [[0 for x in range(w)] for y in range(h)]
			#print data
			n = 0;
			p = 0;

			rows = row_info[len(row_info) - 1]

			for i in range(1,len(mesharray)):

				if( n >  (h1 - 1)):                                            # change here
					n = 0;
					p = p+1;

				s = mesharray[i]
				ln = len(s)
				m = '';

				if (i == len(mesharray)-1 ):
					ln = ln -1

				for j in range(ln-2,0,-1):

					if(s[j] == '"'):
						break;
					else:
						m = m + s[j]
			
				m = m[::-1]
				data[p][n] = m;
				
		 
		 		n = n+1;

			#print data		


		

		else:

			rows = row_info[len(row_info) - 2]
			print "No. of rows in the table: " + rows
			data = "No. of rows in the table: " + rows



		
	except Exception as e:

		print e
		data = "Error in internet connection"

	return data