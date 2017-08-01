import urllib2
from test import split

from data import callserver

###########################################################################################
time = "1-6-2017-11"
data = callserver(0,time);            # callserver(with time or whole data , time for with data is required) ;
                                               # 0 for whole data , time = ""    and    1 for with time , time = "d-m-yyyy-h" (h -> hour in 24 hous format)
print data;




###########################################################################################



               #data analysis part



###########################################################################################
# send message to server to send to user

number = "8860729428"
message = "$Water%20near%20area%2051$"
status = "not-sent"

#print len(message)
#m  = split(message,30)

#url = "http://kumarnikhil1198.000webhostapp.com/storesms.php?number=+918860729428&message=sdf%20sdf&status=not-sent"
url1 = "https://kumarnikhil1198.000webhostapp.com/storesms.php?number=" + number + "&message=" + message + "&status=" + status
content1 = urllib2.urlopen(url1).read()
print content1
