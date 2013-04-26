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
#if DEBUG == 2
		serialPort0.println("UIButton::UIButton()");
#endif
	this->buttonPin = buttonPin;
	this->ledPin = ledPin;
	setup();
}

void UIButton::setup() {
#if DEBUG == 2
		serialPort0.println("UIButton::setup()");
#endif
	pinMode(buttonPin, INPUT);
	pinMode(ledPin, OUTPUT);
}

void UIButton::turnOnLed() {
#if DEBUG == 2
		serialPort0.println("UIButton::turnOnLed()");
		serialPort0.print("Turning on pin: ");
		serialPort0.println(ledPin);
#endif
	digitalWrite(ledPin, HIGH);
}

void UIButton::turnOffLed() {
#if DEBUG == 2
		serialPort0.println("UIButton::turnOffLed()");
		serialPort0.print("Turning off pin: ");
		serialPort0.println(ledPin);
#endif
	digitalWrite(ledPin, LOW);
}

bool UIButton::isPressed() {
	// if (DEBUG) {
	//serialPort0.println("UIButton::isPressed()");
	// }
	bool pressed = digitalRead(buttonPin);
	while (digitalRead(buttonPin)); // Wait for release
	return pressed;
}
