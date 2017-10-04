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

# What does each node of The System measure?:

* Soil Moisture: The full volume of the soil can be broken down into soil particles, roots, air, and liquid water the coats the soil particles.The soil moisture sensor sends electrical impulses and measures the conductivity of the soil which in turn is related to the moisture content of the soil.
* Water is an important necessity for the plants so proper care must be taken to fulfill the crop requirements. It is also to not that the field must not be flooded with water as crops are damaged.The management of the requirements of the water is done by FarmAssist.
* Temperature: The temperature readings of the nodes are much more localized that the weather forecast and provide a sense of the temperature variation in the field. The weather forecast temperature is typically a measure of the air temperature several feet above the ground which is of no significant use to the farmer.
* Humidity: The humidity is sometimes an under-appreciated variable for the farmers.Water evaporates through the pores of the leaves which are open to take in carbon dioxide.A low humidity means a lot of water can be lost through evapotranspiration, which means the plants will require more water.
* Gas Concentration(for storage): In the storage areas the gas sensors are used to measure the amount of methane and smoke. Methane is released when the food rots.In order to check the quality of harvested crop, methane sensors are used.The smoke sensors are used for detecting fire in the storage area.

# What are the devices used in a single node?:

* Esp8266:The ESP8266 is a low-cost Wi-Fi chip with full TCP/IP stack and MCU (microcontroller unit) capability

![alt text](https://github.com/nikhil1198/Agricultural-IOT/blob/master/esp.jpg)

* Soil Moisture Sensor: Measures the volumetric water content in the soil.
![alt text](https://github.com/nikhil1198/Agricultural-IOT/blob/master/soil%20moist.jpg)

* Gas Sensors (MQ2 and MQ4): MQ2 is a smoke sensor and MQ4 is methane sensor.
![alt text](https://github.com/nikhil1198/Agricultural-IOT/blob/master/mq-135-gas-sensor.jpg)

* DHT11: The DHT11 is a basic, ultra low-cost digital temperature and humidity sensor. It uses a capacitive humidity sensor and a thermistor to measure the surrounding air, and spits out a digital signal on the data pin (no analog input pins needed). 
![alt text](https://github.com/nikhil1198/Agricultural-IOT/blob/master/dht11'.jpg)








