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
#include "Config.h"

Config::Config() {
	currentMode = none;
	currentLineSpeed = zero;
	currentVoltage = negOne;
	currentTimeout = never;
}

bool Config::isUIEnabled() {
	return uiEnabled;
}

void Config::enableUI() {
	uiEnabled = true;
}

void Config::disableUI() {
	uiEnabled = false;
}

serialmode Config::getSerialMode() {
	return currentMode;
}

linespeed Config::getLineSpeed() {
	return currentLineSpeed;
}

ttlvoltage Config::getVoltage() {
	return currentVoltage;
}

timeout Config::getTimeout() {
	return currentTimeout;
}

long Config::getTimeoutMilis() {
	switch (currentTimeout) {
		case 0: // tenseconds
			return 10000;
  		case 1: // thirtyseconds
  			return 30000;
  		case 2: // oneminute
  			return 60000;
  		case 3: // fiveminutes
  			return 300000;
  	}
  	return -1;
}

void Config::setMode(serialmode mode) {
	currentMode = mode;
}

void Config::setLineSpeed(linespeed speed) {
	currentLineSpeed = speed;
}

void Config::setVoltage(ttlvoltage voltage) {
	currentVoltage = voltage;
}

void Config::setTimeout(timeout aTimeout) {
	currentTimeout = aTimeout;
}

void Config::setDefaults() {
	setMode(ttl);
	setLineSpeed(oneNineteenTwoK);
	setVoltage(onePointEight);
	setTimeout(thirtyseconds);
}
