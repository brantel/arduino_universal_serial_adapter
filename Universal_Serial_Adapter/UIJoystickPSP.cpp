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
#include "UIJoystickPSP.h"

UIJoystickPSP::UIJoystickPSP(int xAxisPin, int yAxisPin) {
#if DEBUG == 2
		serialPort0.println("UIJoystickPSP::UIJoystickPSP()");
#endif
	this->xAxisPin = xAxisPin;
	this->yAxisPin = yAxisPin;

	upCount = 0;
	downCount = 0;
	leftCount = 0;
	rightCount = 0;

	previousDirection = joyNone;
}

joyDirection UIJoystickPSP::direction() {
	// if (DEBUG) {
	//serialPort0.println("UIJoystickPSP::direction()");
	// }
	// Read the x/y values from the joystick
	xAxisValue = map(analogRead(xAxisPin), 0, 1023, 0, 10);
	yAxisValue = map(analogRead(yAxisPin), 0, 1023, 0, 10);

	if (yAxisValue > 6 ) {
		upCount++;
		if (upCount > 768) {
			upCount = 0;
			return joyUp;
		}
	}

	if (yAxisValue < 4 ) {
		downCount++;
		if (downCount > 768) {
			downCount = 0;
			return joyDown;
		}
	}

	if (xAxisValue > 6) {
		leftCount++;
		if (leftCount > 768) {
			leftCount = 0;
			return joyLeft;
		}
	}

	if (xAxisValue < 4) {
		rightCount++;
		if (rightCount > 768) {
			rightCount = 0;
			return joyRight;
		}
	}

	return joyNone;
}