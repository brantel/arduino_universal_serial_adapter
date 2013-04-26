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
#if DEBUG == 2
		serialPort0.println("Config::UI()");
#endif

	okButton = new UIButton(okButtonPin, okButtonLed);
	cancelButton = new UIButton(cancelButtonPin, cancelButtonLed);
	pspJoystick = new UIJoystickPSP(pspXPin, pspYPin);

	lcd = new UILCD();

	uiTimeout = new Metro(config->getTimeoutMilis());

	startUI();
}

void UI::blinkOKButton() {
	if (config->isUIEnabled()) {
		okButton->turnOffLed();
		okButton->turnOnLed();
	}
	else {
		okButton->turnOnLed();
		okButton->turnOffLed();
	}
}

void UI::blinkCancelButton() {
	if (config->isUIEnabled()) {
		cancelButton->turnOffLed();
		cancelButton->turnOnLed();
	}
	else {
		cancelButton->turnOnLed();
		cancelButton->turnOffLed();
	}
}

void UI::setLCDTimeout() {
	uiTimeout->interval(config->getTimeoutMilis());
}

void UI::resetTimeout() {
	uiTimeout->reset();
}

void UI::startUI() {
#if DEBUG == 2
		serialPort0.println("Config::startUI()");
#endif
	enableUI();
	lcd->start();
}

void UI::disableUI() {
#if DEBUG == 2
		serialPort0.println("Config::disableUI()");
#endif
	config->disableUI();
	lcd->turnOff();
	okButton->turnOffLed();
	cancelButton->turnOffLed();
}

void UI::enableUI() {
#if DEBUG == 2
		serialPort0.println("Config::enableUI()");
#endif
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

#if DEBUG == 2
			serialPort0.print("Joystick Event: ");
			serialPort0.println(joyStickEvent);
#endif
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
