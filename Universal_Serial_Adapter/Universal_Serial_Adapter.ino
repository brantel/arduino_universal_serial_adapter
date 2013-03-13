/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
  by: Mike Crosson
  Nusku Networks
  date: 2013/03/09
  license: CC-BY SA 3.0 - Creative commons share-alike 3.0
  use this code however you'd like, just keep this license and
  attribute.
*/

#include <ColorLCDShield.h>

#include "Project.h"
#include "UI.h"

// Map a mode -> text value
char* modeToText[4] = {
  "Phone UART",
  "DB9 - Normal",
  "DB9 - Null Mdm",
  "Cisco console"
};

// Known and supported line speeds
linespeedinfo linespeeds[6] = {
  {"2400b", 2400},
  {"9600b", 9600},
  {"19.2k", 19200},
  {"38.4k", 38400},
  {"57.5k", 57600},
  {"115k", 115200}
};

// LCD
LCDShield lcd;   // Line length max is 16

// Buttons
int buttonPins[3] = {3, 4, 5};

// Mode info needed
serialmode currentMode = none;
serialmode selectedMode = none;
linespeed currentLineSpeed = zero;

// Defaults
void setDefaults() {
  setMode(phone);
  setSelection(phone);
  setLineSpeed(oneNineteenTwoK);
}

void setup() {
  /* Set up the button pins as inputs, set pull-up resistor */
  for (int i=0; i<3; i++) {
    pinMode(buttonPins[i], INPUT);
    digitalWrite(buttonPins[i], HIGH);
  }
  
  /* Initialize the LCD, set the contrast, clear the screen */
  lcd.init(PHILIPS);
  lcd.contrast(-63);
  lcd.clear(BACKGROUND);
  
  // Print the modes
  //   Uses enum trickery -- don't assign values to serialmode enum values
  for (int i=0; i<modelinespeed; i++) {
    printMode((serialmode)i);
  }
  
  // Print the Rx/Tx/Speed titles
  printTitles();
  
  // Setup defaults
  setDefaults();
}

void loop() {
  // Up
  if (!digitalRead(buttonPins[2])) {
    serialmode newMode = (serialmode)(selectedMode - 1);
    if (newMode >= 0) {
      setSelection(newMode);
    }
    // Wait for release before going on
    while(!digitalRead(buttonPins[2]));
  }

  // Select / Enter
  if (!digitalRead(buttonPins[1])) {
    setMode(selectedMode);
    // Wait for release before going on
    while(!digitalRead(buttonPins[1]));
  }
  
  // Down
  if (!digitalRead(buttonPins[0])) {
    serialmode newMode = (serialmode)(selectedMode + 1);
    if (newMode <= modelinespeed) {
      setSelection(newMode);
    }
    // Wait for release before going on
    while(!digitalRead(buttonPins[0]));
  }
}
