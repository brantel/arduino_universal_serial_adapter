/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
 by: Mike Crosson
 Nusku Networks
 date: 2013/03/09
 license: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute.
 */

#ifndef Config_h
#define Config_h

#include "Project.h"
#include "UI.h"

// Forward declaration of UI
class UI;

// Use global config and ui objects defined / initialized in main ino file
extern UI* ui;

class Config {
private:
	// Mode info needed
	serialmode currentMode;
	linespeed currentLineSpeed;
	ttlvoltage currentVoltage;
	timeout currentTimeout;
	bool uiEnabled;

public:
	Config();
	void setDefaults();
	void setMode(serialmode mode);
	void setLineSpeed(linespeed speed);
	void setVoltage(ttlvoltage voltage);
	void setLCDTimeout(timeout aTimeout);
	serialmode getSerialMode();
	linespeed getLineSpeed();
	float getLineSpeedBaud(); // MUST be an unsigned int for >= 38400 and float for >=115200
	ttlvoltage getVoltage();
	timeout getTimeout();
	int getTimeoutMilis();
	void disableUI();
	void enableUI();
	bool isUIEnabled();
	void processSerialData();
};

#endif
