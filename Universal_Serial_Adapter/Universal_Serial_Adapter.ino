/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
 by: Mike Crosson
 Nusku Networks
 date: 2013/03/09
 license: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute.
 */

#include <Metro.h>

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

UI* ui;
Config* config;

// helper for interrupt method call
void processSerial() {
  config->processSerialData();
}

void setup() {
  Serial.begin(115200);

  config = new Config();
  config->setDefaults();

  ui = new UI();

  // Setup serial IO on an interrupt timer
  // ***THIS MUST BE DONE AFTER new Config()***
  Timer3.initialize(100);                // initialize timer3, value in micro seconds
  Timer3.pwm(timerThreePin, 512);        // setup pwm on appropriate pin, 50% duty cycle
  Timer3.attachInterrupt(processSerial); // attaches method as a timer overflow interrupt
}

void loop() {
  // Serial data is processed via an interrupt so isn't needed in the main loop
  ui->processInputEvents();
  ui->processTimeoutEvents();
}

