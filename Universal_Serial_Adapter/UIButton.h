/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
 by: Mike Crosson
 Nusku Networks
 date: 2013/03/09
 license: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute.
 */

#ifndef UIButton_h
#define UIButton_h

class UIButton {
private:
	int buttonPin;
	int ledPin;

public:
	UIButton(int buttonPin, int ledPin);
	void setup();
	void turnOnLed();
	void turnOffLed();
	bool isPressed();
};

#endif
