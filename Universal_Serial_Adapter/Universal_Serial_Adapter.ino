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

UIButton* okButton;
UIButton* cancelButton;

// Defaults
void setDefaults() {
  //FIXME: Re-enable once new LCD is online
  //setMode(phone);
  //setSelection(phone);
  //setLineSpeed(oneNineteenTwoK);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Setup!");

  // Setup defaults
  setDefaults();

  okButton = new UIButton(okButtonPin, okButtonLed);
  cancelButton = new UIButton(cancelButtonPin, cancelButtonLed);
}

void loop() {
	if (okButton->isPressed()) {
		Serial.println("OK Button Pressed");
	}

	if (cancelButton->isPressed()) {
		Serial.println("Cancel button pressed");
	}
}
