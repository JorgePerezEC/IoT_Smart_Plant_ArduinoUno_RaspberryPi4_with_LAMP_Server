# IoT_Smart_Plant_ArduinoUno_RaspberryPi4_with_LAMP_Server
Implementation of a system that supports the care of a plant with automatic irrigation through the Arduino Uno hardware along with the use of different sensors such as: DHT11, light sensor, hygrometer and ultrasonic; allows the collection of data from the sensors as well as actions performed in the irrigation system through the Raspberry Pi OS, after this stores the data within a LAMP server. 

![prototype](https://user-images.githubusercontent.com/102699851/225760972-5a907c6e-7aa1-4204-95c9-4d6f046d3681.png)

## Installation

1. A LAMP server must be installed on the Raspberry Pi.
2. In the MySQL database create the tables of the `dbScript` script.
3. Load the INO code `ArduinoScript.ino` in the Arduino UNO.
4. Set up the Arduino Uno circuit with the sensors and connect it to the Raspberry Pi to receive the data from the sensors via serial monitor.
5. Execute the python code `TonnyScript.py` to store the data received from the Arduino Uno by serial monitor in the MySQL database.

### Note
This project can also be done using a virtual machine instead of the Raspberry Pi.

## Proyecto Finalizado 
![iot_project](https://user-images.githubusercontent.com/102699851/225761934-7c803d3a-d9e5-4be7-9901-2c0c022279c5.jpg)


