/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
 by: Mike Crosson
 Nusku Networks
 date: 2013/03/09
 license: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute.
 */

#include "Arduino.h"
#include "UIButton.h"

UIButton::UIButton(int buttonPin, int ledPin) {
	this->buttonPin = buttonPin;
	this->ledPin = ledPin;
}

void UIButton::setup() {
	pinMode(buttonPin, INPUT);
	pinMode(ledPin, OUTPUT);
	
	turnOnLed();
}

void UIButton::turnOnLed() {
	digitalWrite(ledPin, HIGH);
}

void UIButton::turnOffLed() {
	digitalWrite(ledPin, LOW);
}

bool UIButton::isPressed() {
	return digitalRead(buttonPin);
}
