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

// Mode info needed
serialmode currentMode = none;
serialmode selectedMode = none;
linespeed currentLineSpeed = zero;
linespeed selectedLineSpeed = zero;
voltage currentVoltage = zero;
voltage selectedVoltage = zero;

// Defaults
void setDefaults() {
  //FIXME: Re-enable once new LCD is online
  //setMode(phone);
  //setSelection(phone);
  //setLineSpeed(oneNineteenTwoK);
}

void setup() {

  // Setup defaults
  setDefaults();

  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  
}
