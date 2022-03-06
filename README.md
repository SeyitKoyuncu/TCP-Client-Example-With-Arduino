# TCP-Client-Example-With-Arduino
This project main purpose is that, led on and off with TCP client in arduino. In inside of project we create tcp client with ethernet shield and then connect to the server. In last step, we take datas from server and with these datas we give energy to the leds or cut to energy. 

Description Of Lınes (You can find more detailed descriptions in inside of code):

    1- Lines between 1-3, necessary libraries.
    2- Lines between 5-10, network variables. (You need to change for your special project)
    3- Lines between 18-26, in the setup part, we starting ethernet and neopixel library and then connect to the server.
    4- Lines between 31-35, necessary variables.
    5- Line 41, clear the buffer then in line 42 check the client is connect to the server correctly or not.
    6- In line 44, we read data and assign it to controlMsg, if it is 0x86 this meaning we read correct data and we can start to led procces.
    7- In line 48, we read data and assing it to recMsg varaible, this variable decision to the which led off choice we want to use, if it is 1 we want to led on just one led,
      if it is 2 we want to all leds on, on the other hand, if it is 3 led off all the leds.
