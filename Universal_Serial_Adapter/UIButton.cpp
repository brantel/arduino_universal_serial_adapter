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
#include "Project.h"

UIButton::UIButton(int buttonPin, int ledPin) {
	this->buttonPin = buttonPin;
	this->ledPin = ledPin;
	setup();
}

void UIButton::setup() {
	pinMode(buttonPin, INPUT);
	pinMode(ledPin, OUTPUT);
}

void UIButton::turnOnLed() {
	if (DEBUG) {
		Serial.print("Turning on pin: ");
		Serial.println(ledPin);
	}
	digitalWrite(ledPin, HIGH);
}

void UIButton::turnOffLed() {
	if (DEBUG) {
		Serial.print("Turning off pin: ");
		Serial.println(ledPin);
	}
	digitalWrite(ledPin, LOW);
}

bool UIButton::isPressed() {
	bool pressed = digitalRead(buttonPin);
	while (digitalRead(buttonPin)); // Wait for release
	return pressed;
}
