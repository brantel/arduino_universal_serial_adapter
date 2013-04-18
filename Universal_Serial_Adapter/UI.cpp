/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
 by: Mike Crosson
 Nusku Networks
 date: 2013/03/09
 license: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute.
 */

#include <Metro.h>

#include "Project.h"
#include "UI.h"

UI::UI() {
	if (DEBUG) {
		Serial.println("Config::UI()");
	}

	okButton = new UIButton(okButtonPin, okButtonLed);
	cancelButton = new UIButton(cancelButtonPin, cancelButtonLed);
	pspJoystick = new UIJoystickPSP(pspXPin, pspYPin);

	lcd = new UILCD(config);

	uiTimeout = new Metro(config->getTimeoutMilis());

	startUI();
}

void UI::setLCDTimeout() {
	uiTimeout->interval(config->getTimeoutMilis());
}

void UI::resetTimeout() {
	uiTimeout->reset();
}

void UI::startUI() {
	if (DEBUG) {
		Serial.println("Config::startUI()");
	}
	enableUI();
	lcd->start();
}

void UI::disableUI() {
	if (DEBUG) {
		Serial.println("Config::disableUI()");
	}
	config->disableUI();
	lcd->turnOff();
	okButton->turnOffLed();
	cancelButton->turnOffLed();
}

void UI::enableUI() {
	if (DEBUG) {
		Serial.println("Config::enableUI()");
	}
	config->enableUI();
	lcd->turnOn();
	okButton->turnOnLed();
	cancelButton->turnOnLed();
	uiTimeout->reset();
}

void UI::processTimeoutEvents() {
	if (uiTimeout->check()) {
		disableUI();
	}
}

void UI::processInputEvents() {
	joyStickEvent = pspJoystick->direction();
	if (joyStickEvent != joyNone) {
		if (!config->isUIEnabled()) {
			enableUI();
			return;
		}

		if (DEBUG) {
			Serial.print("Joystick Event: ");
			Serial.println(joyStickEvent);
		}
		resetTimeout();
		lcd->handleJoystickEvent(joyStickEvent);
	}

	if (okButton->isPressed()) {
		if (!config->isUIEnabled()) {
			enableUI();
			return;
		}
		resetTimeout();
		lcd->handleOkButtonEvent();
	}

	if (cancelButton->isPressed()) {
		if (!config->isUIEnabled()) {
			enableUI();
			return;
		}
		resetTimeout();
		lcd->handleCancelButtonEvent();
	}
}
