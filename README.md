# PULSE-RATE-MONITORING
Heart Beat Detection and Monitoring System using Arduino UNO that detects heart beat of user using Pulse Sensor and uploads readings to [ThingSpeak](https://thingspeak.com/) Server using the ESP8266 Wi-Fi module , so that Pulse Rate can be monitored from anywhere in the world over the Internet.
## Getting Started

This project is about designing and creating a Heart Beat Detection and Monitoring System using Arduino that will detect the heart beat using the Pulse Sensor and display readings in BPM (Beats Per Minute) on the LCD connected to it and also uploads it to ThingSpeak Server using its API to visualize and analyse data received.

### Requirements
* [Arduino Uno](https://www.arduino.cc/en/Guide/ArduinoUno) - Hardware
* [ThingSpeak](https://thingspeak.com/apps) - Account On ThingSpeak To Visualize/Analyse Data
* [ESP8266 Wifi Module](https://www.espressif.com/en/products/hardware/esp8266ex/overview) - Hardware
* [Pulse Sensor](https://pulsesensor.com/) - Hardware
* LCD,10k Potentiometer,1k Resistors,220 Ohm Resistors,Connecting wires

### Prerequisites
* [Arduino IDE](https://www.arduino.cc/en/main/software)
* [PulseSensorPlayground Library](http://downloads.arduino.cc/libraries/github.com/WorldFamousElectronics/PulseSensor_Playground-1.2.2.zip)
* [SoftwareSerial Library](https://www.arduino.cc/en/Reference/softwareSerial)

### Circuit Diagram
![alt text](https://raw.githubusercontent.com/snehsagarajput/pulse-rate-monitor/master/circuit%20diagram.jpg)
