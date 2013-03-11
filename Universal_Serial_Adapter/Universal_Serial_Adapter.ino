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
    S2: Select/Enter
    S3: Down
  
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

// Defaults
void setDefaults() {
  setMode(phone);
  setSelection(phone);
  setLineSpeed(oneNineteenTwoK);
}

void setLineSpeed(linespeed aLineSpeed) {
  currentLineSpeed = aLineSpeed;
  bool sel = selectedMode == modelinespeed ? true : false;
  printLineSpeed(aLineSpeed, sel);
}

void setMode(serialmode aMode) {
  if (aMode != modelinespeed) {
    serialmode previousMode = currentMode;
    currentMode = aMode;
    
    lcd.setStr(" ", xLoc(previousMode), yLoc(0), TEXT, BACKGROUND);
    lcd.setStr("*", xLoc(currentMode), yLoc(0), TEXT, BACKGROUND);
  }
}

void setSelection(serialmode aMode) {
  serialmode previousSelection = selectedMode;
  selectedMode = aMode;
  
  int yLocOne = yLoc(1);
  
  int xSelected = 0;
  if (selectedMode != modelinespeed) {
    xSelected = xLoc(selectedMode) + CHAR_HEIGHT;
  }
  
  int xPrevious = 0;
  if (previousSelection != modelinespeed) {
    xPrevious = xLoc(previousSelection) + CHAR_HEIGHT;
  }

  int previousLength = 0;
  if (previousSelection != modelinespeed) {
    previousLength = strlen(modeToText[previousSelection]) * CHAR_WIDTH;
  }
  
  int selectedLength = 0;
  if (selectedMode != modelinespeed) {
    selectedLength = strlen(modeToText[selectedMode]) * CHAR_WIDTH;
  }
  
  if (selectedMode != modelinespeed) {
    lcd.setLine(xSelected, yLocOne, xSelected, yLocOne + selectedLength, HILIGHT);
  }
  else {
    printLineSpeed(currentLineSpeed, true);
  }
  
  if (previousSelection != modelinespeed) {
    lcd.setLine(xPrevious, yLocOne, xPrevious, yLocOne + previousLength, BACKGROUND);
  }
  else {
    printLineSpeed(currentLineSpeed, false);
  }
}

void printTitles() {
  lcd.setStr(" RX  Ln Spd  Tx ", xLoc(5), 0, TEXT, BACKGROUND);
}

void printMode(serialmode aMode) {
  lcd.setStr(modeToText[aMode], xLoc(aMode), yLoc(1), TEXT, BACKGROUND);
}

void printLineSpeed(linespeed aLineSpeed, bool selected) {
  int xPosText = xLoc(6);
  int yPosText = yLoc(5);
  
  int xPosLine = xLoc(7);
  int yPosLine = yLoc(5);
  
  char* toPrint = linespeeds[aLineSpeed].description;
  int length = strlen(toPrint);
  
  lcd.setStr("       ", xPosText, yPosText, BACKGROUND, BACKGROUND);
  lcd.setLine(xPosLine, yPosLine, xPosLine, yPosLine + 7 * CHAR_WIDTH, BACKGROUND);

  lcd.setStr(toPrint, xPosText, yPosText, TEXT, BACKGROUND);
  if (selected) {
    lcd.setLine(xPosLine, yPosLine, xPosLine, yPosLine + length * CHAR_WIDTH, HILIGHT);
  }
}

void printRx(bool show) {
  int vertXPosStart = xLoc(6.25);
  int vertYPosStart = yLoc(1.5);
  int vertXPosEnd = xLoc(7.25);
  int vertYPosEnd = yLoc(1.5);

  int lftXPosStart = vertXPosEnd;
  int lftYPosStart = vertYPosStart;
  int lftXPosEnd = vertXPosStart + (CHAR_HEIGHT / 2);
  int lftYPosEnd = vertYPosStart - CHAR_WIDTH;

  int rtXPosStart = vertXPosEnd;
  int rtYPosStart = vertYPosStart;
  int rtXPosEnd = vertXPosStart + (CHAR_HEIGHT / 2);
  int rtYPosEnd = vertYPosStart + CHAR_WIDTH;

  int color = show ? EMERALD : BACKGROUND;

  lcd.setLine(vertXPosStart, vertYPosStart, vertXPosEnd, vertYPosEnd, color);
  lcd.setLine(lftXPosStart, lftYPosStart, lftXPosEnd, lftYPosEnd, color);
  lcd.setLine(rtXPosStart, rtYPosStart, rtXPosEnd, rtYPosEnd, color);
}

void printTx(bool show) {
  int vertXPosStart = xLoc(6.25);
  int vertYPosStart = yLoc(13.5);
  int vertXPosEnd = xLoc(7.25);
  int vertYPosEnd = yLoc(13.5);

  int lftXPosStart = vertXPosStart;
  int lftYPosStart = vertYPosStart;
  int lftXPosEnd = vertXPosStart + (CHAR_HEIGHT / 2);
  int lftYPosEnd = vertYPosStart - CHAR_WIDTH;

  int rtXPosStart = vertXPosStart;
  int rtYPosStart = vertYPosStart;
  int rtXPosEnd = vertXPosStart + (CHAR_HEIGHT / 2);
  int rtYPosEnd = vertYPosStart + CHAR_WIDTH;
  
  int color = show ? SKYBLUE : BACKGROUND;

  lcd.setLine(vertXPosStart, vertYPosStart, vertXPosEnd, vertYPosEnd, color);
  lcd.setLine(lftXPosStart, lftYPosStart, lftXPosEnd, lftYPosEnd, color);
  lcd.setLine(rtXPosStart, rtYPosStart, rtXPosEnd, rtYPosEnd, color);
}
