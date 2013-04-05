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

// Button state tracking
int okButtonState = 0; 
int prevOkButtonState = okButtonState;
int cancelButtonState = 0;
int prevCancelButtonState = prevCancelButtonState;

// PSP joystick tracking
long pspUpCount = 0; // Used to slow down how fast we repeat up movement
long pspDownCount = 0; // Used to slow down how fast we repeat down movement
int pspXAxisValue;
int pspYAxisValue;

// Mode info needed
serialmode currentMode = none;
serialmode selectedMode = none;
linespeed currentLineSpeed = zero;

// Defaults
void setDefaults() {
  //FIXME: Re-enable once new LCD is online
  //setMode(phone);
  //setSelection(phone);
  //setLineSpeed(oneNineteenTwoK);
}

void setup() {
  // Buttons
  pinMode(okButtonPin, INPUT);
  pinMode(cancelButtonPin, INPUT);

  // Button LEDs
  pinMode(okButtonLed, OUTPUT);
  digitalWrite(okButtonLed, HIGH);
  pinMode(cancelButtonLed, OUTPUT);
  digitalWrite(cancelButtonLed, HIGH);

  // Setup defaults
  setDefaults();

  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // Read the x/y values from the joystick
  pspXAxisValue=map(analogRead(pspXPin), 0, 1023, 0, 10);
  pspYAxisValue=map(analogRead(pspYPin), 0, 1023, 0, 10);

  // Move cursor Up
  if (pspYAxisValue > 6 ) {
    pspUpCount++;
    if (pspUpCount > 768) {
      pspUpCount = 0;
      serialmode newMode = (serialmode)(selectedMode - 1);
      if (newMode >= 0) {
        //FIXME: Re-enable once new LCD is online
        //setSelection(newMode);
      }
    }
  }
  else {
    pspUpCount = 0;
  }

  // Move cursor Down
  if (pspYAxisValue < 4 ) {
    pspDownCount++;
    if (pspDownCount > 768) {
      serialmode newMode = (serialmode)(selectedMode + 1);
      if (newMode <= modelinespeed) {
        //FIXME: Re-enable once new LCD is online
        //setSelection(newMode);
      }
      pspDownCount = 0;
    }
  }
  else {
    pspDownCount = 0;
  }


  // Select / Enter
  if (digitalRead(okButtonPin)) {
    //FIXME: Re-enable once new LCD is online
    //setMode(selectedMode);
  }
}



