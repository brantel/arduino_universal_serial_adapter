/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
 by: Mike Crosson
 Nusku Networks
 date: 2013/03/09
 license: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute.
 */

#include <Wire.h>

#include "Project.h"
#include "Config.h"
#include "UIButton.h"
#include "UIJoystickPSP.h"
#include "UILCD.h"
#include "UI.h"

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SD.h>
#include <SPI.h>

#include <TimerThree.h>
#include <Metro.h>
#include "RTClib.h"

UI* ui;
Config* config;
RTC_DS1307 rtc;
File dataFile;

// helper for interrupt method call
void processSerial() {
  config->processSerialData();
}

void setup() {
  // Setup various IO busses
  Serial.begin(115200);
  Wire.begin();

  // Ensure RTC is set to run on battery
  // clear /EOSC bit
  // Sometimes necessary to ensure that the clock
  // keeps running on just battery power. Once set,
  // it shouldn't need to be reset but it's a good
  // idea to make sure.
  Wire.beginTransmission(0x68); // address DS3231
  Wire.write(0x0E); // select register
  Wire.write(0b00011100); // write register bitmap, bit 7 is /EOSC
  Wire.endTransmission();

  rtc.begin();

  // Stuff used for serial and UI
  config = new Config();
  config->setDefaults();
  ui = new UI();

  // Setup serial IO on an interrupt timer
  // ***THIS MUST BE DONE AFTER new Config()***
  Timer3.initialize(100);                // initialize timer3, value in micro seconds
  Timer3.pwm(timerThreePin, 512);        // setup pwm on appropriate pin, 50% duty cycle
  Timer3.attachInterrupt(processSerial); // attaches method as a timer overflow interrupt

  dataFile = SD.open("datalog.txt", FILE_WRITE);
}

void loop() {
  // Serial data is processed via an interrupt so isn't needed in the main loop
  ui->processInputEvents();
  ui->processTimeoutEvents();
}

