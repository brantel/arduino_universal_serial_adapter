Arduino Universal Serial Adapter
================================
Everything you need to create an Arduino based serial adapter designed to work with
- Phone UART chips
- Standard DB9 serial ports
- Null modem serial ports
- Cisco serial consoles

The idea is to have 1 serial adapter that takes care of all of your DB9 / null modem / goofy pinouts in one package.


Code
====
IDE / Environment
-----------------
This project was developed using stino (Sublime Text 2 plugin).  It works slightly differently (read: more powerful) than the standard Arduino IDE.  This project may or may not build under the Arduino IDE.

Configuration
-------------
The `Project.h` and `Project.cpp` files define the pinouts in use, Arduino pinout and a number of other items that may vary between builds.  Please read through these [short] files and update the pinouts, addresses and anything else that may be different before uploading to your Arduino.

Prototype
=========
![Universal Arduino Serial Adapter](https://raw.github.com/mcrosson/arduino_universal_serial_adapter/master/Pictures/DSCN2938.JPG)

Parts
-----
* Arduino Mega
* AdaFruit 1.8" LCD with MicroSD Card Slot
* PSP Joystick
* LED backlit buttons
* Spark Fun MicroUSB breakout
* AdaFruit logic level converter (bi-directional)
* RJ-45 jacks
* DB9 jack
* Maxim Max3232 RS232 to TTL DIP IC's

Credits / Thanks
================
* ChildOfTheHorn/Stacy Wylie
* Adam Outler
* Motorhead
* utkanos
* bhundven

Articles / Information Used For Project
=======================================
* http://forum.xda-developers.com/showthread.php?t=1901376
* http://forums.hackaday.com/viewtopic.php?f=3&t=623
* http://petervanhoyweghen.wordpress.com/2012/11/08/using-the-leonardo-as-usb-to-* serial-converter/
* http://www.cellbots.com/how-to/handling-3-3v-to-5v-logic-level-conversion/
* https://plus.google.com/104711040110222472212/posts/3764HBYeb2X
* http://www.cutedigi.com/arduino-shields/rs232-shield-for-arduino.html
* http://www.arduino.cc/en/Tutorial/SoftwareSerial
* http://arduino.cc/en/Tutorial/ArduinoSoftwareRS232
* http://www.ossmann.com/5-in-1.html
* http://www.lammertbies.nl/comm/cable/RS-232.html
* http://www.usconverters.com/index.php?main_page=page&id=61&chapter=0