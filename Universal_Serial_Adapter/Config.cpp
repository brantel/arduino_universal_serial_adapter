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
	if (DEBUG) {
		Serial.println("Config::Config()");
	}
	currentMode = none;
	currentLineSpeed = zero;
	currentVoltage = negOne;
	currentTimeout = never;

	pinMode(voltagePinOnePointEight, OUTPUT);
	pinMode(voltagePinThreePointThree, OUTPUT);
	pinMode(voltagePinFivePointZero, OUTPUT);

	if (DEBUG) {
		Serial.begin(115200);
	}
}

bool Config::isUIEnabled() {
	if (DEBUG) {
		Serial.println("Config::isUIEnabled()");
	}
	return uiEnabled;
}

void Config::enableUI() {
	if (DEBUG) {
		Serial.println("Config::enableUI()");
	}
	uiEnabled = true;
}

void Config::disableUI() {
	if (DEBUG) {
		Serial.println("Config::disableUI()");
	}
	uiEnabled = false;
}

serialmode Config::getSerialMode() {
	if (DEBUG) {
		Serial.println("Config::getSerialMode()");
	}
	return currentMode;
}

linespeed Config::getLineSpeed() {
	if (DEBUG) {
		Serial.println("Config::getLineSpeed()");
	}
	return currentLineSpeed;
}

float Config::getLineSpeedBaud() {
	if (DEBUG) {
		Serial.println("Config::getLineSpeedBaud()");
	}

	switch (currentLineSpeed) {
		case 0: // twentyFourHundredBaud
			return 2400;
			break;
		case 1: // ninetySixHundredBaud
			return 9600;
			break;
		case 2: // nineteenTwoK
			return 19200;
			break;
		case 3: // thirtyeightFourK
			return 38400;
			break;
		case 4: // fiftysevenFiveK
			return 57600;
			break;
		case 5: // oneNineteenTwoK
			return 115200;
			break;
	}
}

ttlvoltage Config::getVoltage() {
	if (DEBUG) {
		Serial.println("Config::getVoltage()");
	}
	return currentVoltage;
}

timeout Config::getTimeout() {
	if (DEBUG) {
		Serial.println("Config::getTimeout()");
	}
	return currentTimeout;
}

int Config::getTimeoutMilis() {
	if (DEBUG) {
		Serial.println("Config::getTimeoutMilis()");
	}
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
	if (DEBUG) {
		Serial.println("Config::setMode()");
		Serial.print("    Setting ttl line speed to:");
		float baudrate = this->getLineSpeedBaud();
		Serial.println(baudrate);
	}

	switch (currentMode) {
		case 1: // ttl
			Serial3.end();
			break;
		case 2: // db9_null
			Serial2.end();
			break;
		case 3: // cisco
			Serial1.end();
			break;
	}

	switch (mode) {
		case 0: // ttl
			Serial3.begin(getLineSpeedBaud());
			break;
		case 1: // db9_null
			Serial2.begin(getLineSpeedBaud());
			break;
		case 2: // cisco
			Serial1.begin(getLineSpeedBaud());
			break;
	}

	currentMode = mode;
}

void Config::setLineSpeed(linespeed aLineSpeed) {
	if (DEBUG) {
		Serial.println("Config::setLineSpeed()");
	}
	currentLineSpeed = aLineSpeed;
	Serial.end();
	Serial.begin(getLineSpeedBaud());
	setMode(currentMode);
}

void Config::setVoltage(ttlvoltage voltage) {
	if (DEBUG) {
		Serial.println("Config::setVoltage()");
	}
	currentVoltage = voltage;

	digitalWrite(voltagePinOnePointEight, LOW);
	digitalWrite(voltagePinThreePointThree, LOW);
	digitalWrite(voltagePinFivePointZero, LOW);

	switch (voltage) {
		case 0: // onePointEight
			digitalWrite(voltagePinOnePointEight, HIGH);
			break;
		case 1: // threePointThree
			digitalWrite(voltagePinThreePointThree, HIGH);
			break;
		case 2: // five
			digitalWrite(voltagePinFivePointZero, HIGH);
			break;
	}

}

void Config::setLCDTimeout(timeout aTimeout) {
	if (DEBUG) {
		Serial.println("Config::setTimeout()");
	}
	currentTimeout = aTimeout;
}

void Config::setDefaults() {
	if (DEBUG) {
		Serial.println("Config::setDefaults()");
	}
	setVoltage(onePointEight);
	setLineSpeed(oneFifteenTwoK);
	setMode(ttl);
	setLCDTimeout(thirtyseconds);
}

void Config::processSerialData() {
	//if (DEBUG) {
	//	Serial.println("Config::processSerialData()");
	//}
	switch (currentMode) {
		case 0: // ttl
			if (Serial3.available()) {
				int inByte = Serial3.read();
				Serial.write(inByte);
			}
			if (Serial.available()) {
				int inByte = Serial.read();
				Serial3.write(inByte);
			}
			break;
		case 1: // db9_null
			if (Serial2.available()) {
				int inByte = Serial2.read();
				Serial.write(inByte);
			}
			if (Serial.available()) {
				int inByte = Serial.read();
				Serial2.write(inByte);
			}
			break;
		case 2: // cisco
			if (Serial1.available()) {
				int inByte = Serial1.read();
				Serial.write(inByte);
			}
			if (Serial.available()) {
				int inByte = Serial.read();
				Serial1.write(inByte);
			}
			break;
	}
}
