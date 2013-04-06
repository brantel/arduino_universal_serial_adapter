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
#include "UIButton.h"
#include "UIJoystickPSP.h"

UIButton* okButton;
UIButton* cancelButton;
UIJoystickPSP* pspJoystick;

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
  pspJoystick = new UIJoystickPSP(pspXPin, pspYPin);
}

void loop() {
	int direction = pspJoystick->direction();
	if (direction != joyNone) {
		Serial.print("Joystick Direction: ");
		Serial.println(direction);
	}
}
