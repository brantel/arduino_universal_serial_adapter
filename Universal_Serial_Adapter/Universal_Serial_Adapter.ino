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
#include "UILCD.h"

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SD.h>
#include <SPI.h>

UIButton* okButton;
UIButton* cancelButton;
UIJoystickPSP* pspJoystick;
UILCD* lcd;

joyDirection joyStickEvent;

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

  lcd = new UILCD();
  lcd->startUI();
}

void loop() {
  joyStickEvent = pspJoystick->direction();
  if (joyStickEvent != joyNone) {
    if (DEBUG) {
      Serial.print("Joystick Event: ");
      Serial.println(joyStickEvent);
    }
    lcd->handleJoystickEvent(joyStickEvent);
  }

  if (okButton->isPressed()) {
    lcd->handleOkButtonEvent();
  }

  if (cancelButton->isPressed()) {
    lcd->handleCancelButtonEvent();
  }
}

