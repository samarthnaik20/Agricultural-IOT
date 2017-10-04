# Agricultural-IOT

# Introduction:

* "Agricultural IOT" is a system that gathers data of the the environmental conditions that are prevalent in the field as well as the storage areas.This data is gathered at multiple points.
* It uses this data to inform the farmer the requirements of the crop that would eventually lead to the enhancement of the crop yield.

# What this system does?:

* Continuous monitoring: The System tracks soil moisture, temperature, humidity, gas content(for storage).
* Real-time guidance: The System provides real time notification to the farmer based on the farm conditions.
* Region specific guidance: The System provides notification as to the requirements of the different regions of the field.
* Data preservation: The System stores the data of the farm on an online server, which can be used for  analysis of soil over a large region, crop yield prediction, predicting the crop best compatible with climatic as well as soil conditions. 

# System Architecture:

* The complete system “Agricultural IoT” consists of a number of individual nodes(field nodes) that gather data at that point of the field. This data is then sent to a central node named as “data node” via shortest path in the network available at that point of time.
* This network that we have created is using esp8266 module. These esps communicate with each other using wifi signals. The esps gather the different sensors data and then transfer it. 
* A SIM card enabled Data hub is placed in the field anywhere near the mesh so as to collect all the data from each and every node and each and every sensor. The Data hub consists of ESP8266, Arduino, GSM module.
* The collected data is uploaded to the servers for further processing with respect to crops. Once the the data has been processed the farmer is notified via SMS to take necessary action. 

![alt text](https://github.com/nikhil1198/Agricultural-IOT/blob/master/image.png)



