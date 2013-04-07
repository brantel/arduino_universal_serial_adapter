/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
 by: Mike Crosson
 Nusku Networks
 date: 2013/03/09
 license: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute.
 */

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

#include <Metro.h>

UI* ui;
Config* config;

Metro* uiTimeout;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup!");

  config = new Config();
  config->setDefaults();

  ui = new UI(config);
  
  uiTimeout = new Metro(config->getTimeoutMilis(), false);
}

void loop() {
  // FIXME: Move timer to UI under its own method
  if (uiTimeout->check()) {
    ui->disableUI();
  }

  ui->processInputEvents();
}

