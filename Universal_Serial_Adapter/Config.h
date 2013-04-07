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

#ifndef Config_h
#define Config_h

class Config {
private:
	// Mode info needed
	serialmode currentMode;
	linespeed currentLineSpeed;
	ttlvoltage currentVoltage;

public:
	Config();
	void setDefaults();
	void setMode(serialmode mode);
	void setLineSpeed(linespeed speed);
	void setVoltage(ttlvoltage voltage);
	serialmode getSerialMode();
	linespeed getLineSpeed();
	ttlvoltage getVoltage();
};

#endif