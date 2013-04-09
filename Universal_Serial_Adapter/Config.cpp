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

int Config::getLineSpeedBaud() {
	switch (currentLineSpeed) {
		case 1: // twentyFourHundredBaud
			return 2400;
			break;
		case 2: // ninetySixHundredBaud
			return 9600;
			break;
		case 3: // nineteenTwoK
			return 19200;
			break;
		case 4: // thirtyeightFourK
			return 38400;
			break;
		case 5: // fiftysevenFiveK
			return 57600;
			break;
		case 6: // oneNineteenTwoK
			return 119200;
			break;
	}
}

ttlvoltage Config::getVoltage() {
	return currentVoltage;
}

timeout Config::getTimeout() {
	return currentTimeout;
}

int Config::getTimeoutMilis() {
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
	switch (currentMode) {
		case 1: // ttl
			Serial1.end();
			break;
		case 2: // db9_null
			Serial2.end();
			break;
		case 3: // cisco
			Serial3.end();
			break;
	}

	switch (mode) {
		case 1: // ttl
			Serial1.begin(getLineSpeedBaud());
			break;
		case 2: // db9_null
			Serial2.begin(getLineSpeedBaud());
			break;
		case 3: // cisco
			Serial3.begin(getLineSpeedBaud());
			break;
	}

	currentMode = mode;
}

void Config::setLineSpeed(linespeed speed) {
	currentLineSpeed = speed;
}

void Config::setVoltage(ttlvoltage voltage) {
	currentVoltage = voltage;
	int shiftNumber = shiftOff;
	switch (voltage) {
		case 1: // onePointEight
			shiftNumber = shift18V;
			break;
		case 2: // threePointThree
			shiftNumber = shift33V;
			break;
		case 3: // five
			shiftNumber = shift50V;
			break;
	}

	// Use bit shifter to activate the proper voltage regulator
	digitalWrite(shifterLatchPin, LOW);
    shiftOut(shifterDataPin, shifterClockPin, MSBFIRST, shiftNumber);
    digitalWrite(shifterLatchPin, HIGH);
}

void Config::setTimeout(timeout aTimeout) {
	currentTimeout = aTimeout;
}

void Config::setDefaults() {
	setVoltage(onePointEight);
	setLineSpeed(oneNineteenTwoK);
	setMode(ttl);
	setTimeout(thirtyseconds);
}

void Config::processSerialData() {
	switch (currentMode) {
		case 1: // ttl
			if (Serial1.available()) {
				int inByte = Serial1.read();
				Serial.write(inByte);
			}
			if (Serial.available()) {
				int inByte = Serial.read();
				Serial1.write(inByte);
			}
			break;
		case 2: // db9_null
			if (Serial2.available()) {
				int inByte = Serial2.read();
				Serial.write(inByte);
			}
			if (Serial.available()) {
				int inByte = Serial.read();
				Serial2.write(inByte);
			}
			break;
		case 3: // cisco
			if (Serial3.available()) {
				int inByte = Serial3.read();
				Serial.write(inByte);
			}
			if (Serial.available()) {
				int inByte = Serial.read();
				Serial3.write(inByte);
			}
			break;
	}
}