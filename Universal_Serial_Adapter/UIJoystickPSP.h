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

#ifndef UIJoystickPSP_h
#define UIJoystickPSP_h

enum joyDirection { 
  joyUp,
  joyDown,
  joyLeft,
  joyRight,
  joyNone=-1
};

class UIJoystickPSP {
private:
	int xAxisPin, yAxisPin; // Pins in use
	int xAxisValue, yAxisValue; // Values read from pins
	int upCount, downCount, leftCount, rightCount; // Counts to slow down repeat

	joyDirection previousDirection;

	// int readXAxisValue();
	// int readYAxisValue();

public:
	UIJoystickPSP(int xAxisPin, int yAxisPin);
	joyDirection direction();
};

#endif