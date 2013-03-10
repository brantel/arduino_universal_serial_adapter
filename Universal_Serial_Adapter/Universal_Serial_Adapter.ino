/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
  by: Mike Crosson
  Nusku Networks
  date: 2013/03/09
  license: CC-BY SA 3.0 - Creative commons share-alike 3.0
  use this code however you'd like, just keep this license and
  attribute.
  
  This sketch currently only shows the four serial modes and
  uses S1-S3 to select the current mode.
  
  A trailing * after the mode indicates the current mode
  
  Button Map:
    S1: Up
    S2: Down
    S3: Select/Enter
  
  Serial Modes:
    Phone UART
    DB9 Normal
    DB9 Null Modem
    Cisco console
*/

#include <ColorLCDShield.h>

#include "Project.h"

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
  for (int i=0; i<=cisco; i++) {
    printMode((serialmode)i);
  }
  
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
    if (newMode <= cisco) {
      setSelection(newMode);
    }
    // Wait for release before going on
    while(!digitalRead(buttonPins[0]));
  }
}

void setMode(serialmode aMode) {
  serialmode previousMode = currentMode;
  currentMode = aMode;
  lcd.setStr(" ", xLoc(previousMode), yLoc(0), TEXT, BACKGROUND); // Clear old *
  lcd.setStr("*", xLoc(currentMode), yLoc(0), TEXT, BACKGROUND); // Add new *
}

void setSelection(serialmode aMode) {
  serialmode previousSelection = selectedMode;
  selectedMode = aMode;
  int previousLength = strlen(modeToText[previousSelection]) * CHAR_WIDTH;
  int selectedLength = strlen(modeToText[selectedMode]) * CHAR_WIDTH;
  lcd.setLine(xLoc(selectedMode) + CHAR_HEIGHT, yLoc(1), xLoc(selectedMode) + CHAR_HEIGHT, yLoc(1) + selectedLength, HILIGHT);
  lcd.setLine(xLoc(previousSelection) + CHAR_HEIGHT, yLoc(1), xLoc(previousSelection) + CHAR_HEIGHT, yLoc(1) + previousLength, BACKGROUND);
}

void printMode(serialmode aMode) {
  lcd.setStr(modeToText[aMode], xLoc(aMode), yLoc(1), TEXT, BACKGROUND);
}

