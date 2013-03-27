/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
 by: Mike Crosson
 Nusku Networks
 date: 2013/03/09
 license: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute.
 */

#include "ColorLCDShield.h"

#include "Project.h"
#include "UI.h"

const int okButtonPin= 22;
const int cancelButtonPin = 23;

// variables will change:
int okButtonState = 0; 
int prevOkButtonState = okButtonState;
int cancelButtonState = 0;
int prevCancelButtonState = 0;

long upCount = 0;
long downCount = 0;

const int Left = 1;
const int Right = 2;
const int Up = 3;
const int Down = 4;

int xpin = 0; // After GND / @ edge
int ypin = 1; // Between VCC and gnd

int xAxis;
int yAxis;
char* myStrings[]={
  "Left","Right","Up","Down"};
int button;

// Map a mode -> text value
char* modeToText[4] = {
  "Phone UART",
  "DB9 - Normal",
  "DB9 - Null Mdm",
  "Cisco console"
};

// Known and supported line speeds
linespeedinfo linespeeds[6] = {
  {
    "2400b", 2400  }
  ,
  {
    "9600b", 9600  }
  ,
  {
    "19.2k", 19200  }
  ,
  {
    "38.4k", 38400  }
  ,
  {
    "57.5k", 57600  }
  ,
  {
    "115k", 115200  }
};

// LCD
LCDShield lcd;   // Line length max is 16

// Buttons
int buttonPins[3] = {
  3, 4, 5};

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

  pinMode(okButtonPin, INPUT);
  pinMode(cancelButtonPin, INPUT);

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
  xAxis=map(analogRead(xpin), 0, 1023, 0, 10);
  yAxis=map(analogRead(ypin), 0, 1023, 0, 10);

  // Up
  if (yAxis > 6 ) {
    upCount++;
    if (upCount > 768) {
      upCount = 0;
      serialmode newMode = (serialmode)(selectedMode - 1);
      if (newMode >= 0) {
        setSelection(newMode);
      }
    }
  }
  else {
    upCount = 0;
  }

  // Select / Enter
  if (digitalRead(okButtonPin)) {
    setMode(selectedMode);
  }

  // Down
  if (yAxis < 4 ) {
    downCount++;
    if (downCount > 768) {
      serialmode newMode = (serialmode)(selectedMode + 1);
      if (newMode <= modelinespeed) {
        setSelection(newMode);
      }
      downCount = 0;
    }
  }
  else {
    downCount = 0;
  }
}

