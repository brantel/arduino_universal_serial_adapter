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
#include "UI.h"

Config::Config() {
#if DEBUG == 2
		serialPort0.println("Config::Config()");
#endif

	currentMode = none;
	currentLineSpeed = zero;
	currentVoltage = negOne;
	currentTimeout = never;

	pinMode(voltagePinOnePointEight, OUTPUT);
	pinMode(voltagePinThreePointThree, OUTPUT);
	pinMode(voltagePinFivePointZero, OUTPUT);
}

bool Config::isUIEnabled() {
#if DEBUG == 2
		serialPort0.println("Config::isUIEnabled()");
#endif
	return uiEnabled;
}

void Config::enableUI() {
#if DEBUG == 2
		serialPort0.println("Config::enableUI()");
#endif
	uiEnabled = true;
}

void Config::disableUI() {
#if DEBUG == 2
		serialPort0.println("Config::disableUI()");
#endif
	uiEnabled = false;
}

serialmode Config::getSerialMode() {
#if DEBUG == 2
		serialPort0.println("Config::getSerialMode()");
#endif
	return currentMode;
}

linespeed Config::getLineSpeed() {
#if DEBUG == 2
		serialPort0.println("Config::getLineSpeed()");
#endif
	return currentLineSpeed;
}

float Config::getLineSpeedBaud() {
#if DEBUG == 2
		serialPort0.println("Config::getLineSpeedBaud()");
#endif

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
#if DEBUG == 2
		serialPort0.println("Config::getVoltage()");
#endif
	return currentVoltage;
}

timeout Config::getTimeout() {
#if DEBUG == 2
		serialPort0.println("Config::getTimeout()");
#endif
	return currentTimeout;
}

int Config::getTimeoutMilis() {
#if DEBUG == 2
		serialPort0.println("Config::getTimeoutMilis()");
#endif
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
#if DEBUG == 2
		serialPort0.println("Config::setMode()");
		serialPort0.print("    Setting ttl line speed to:");
		float baudrate = this->getLineSpeedBaud();
		serialPort0.println(baudrate);
#endif

	switch (currentMode) {
		case 1: // ttl
			serialPort3.end();
			break;
		case 2: // db9_null
			serialPort2.end();
			break;
		case 3: // cisco
			serialPort1.end();
			break;
	}

	switch (mode) {
		case 0: // ttl
			serialPort3.begin(getLineSpeedBaud());
			break;
		case 1: // db9_null
			serialPort2.begin(getLineSpeedBaud());
			break;
		case 2: // cisco
			serialPort1.begin(getLineSpeedBaud());
			break;
	}

	currentMode = mode;
}

void Config::setLineSpeed(linespeed aLineSpeed) {
#if DEBUG == 2
		serialPort0.println("Config::setLineSpeed()");
#endif
	currentLineSpeed = aLineSpeed;
	serialPort0.end();
	serialPort0.begin(getLineSpeedBaud());
	setMode(currentMode);
}

void Config::setVoltage(ttlvoltage voltage) {
#if DEBUG == 2
		serialPort0.println("Config::setVoltage()");
#endif
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
#if DEBUG == 2
		serialPort0.println("Config::setTimeout()");
#endif
	currentTimeout = aTimeout;
	ui->setLCDTimeout();
}

void Config::setDefaults() {
#if DEBUG == 2
		serialPort0.println("Config::setDefaults()");
#endif
	setVoltage(onePointEight);
	setLineSpeed(oneFifteenTwoK);
	setMode(ttl);
	setLCDTimeout(thirtyseconds);
}

void Config::processSerialData() {
	//if (DEBUG) {
	//	Serial.println("Config::processSerialData()");
	//}
	//#if DEBUG == 2
    //DateTime now = rtc.now();
    //Serial.print(now.year(), DEC);
    //Serial.print('/');
    //Serial.print(now.month(), DEC);
    //Serial.print('/');
    //Serial.print(now.day(), DEC);
    //Serial.print(' ');
    //Serial.print(now.hour(), DEC);
    //Serial.print(':');
    //Serial.print(now.minute(), DEC);
    //Serial.print(':');
    //Serial.print(now.second(), DEC);
    //Serial.println();
	//#endif
	switch (currentMode) {
		case 0: // ttl
			if (serialPort3.available()) {
				int inByte = serialPort3.read();
				serialPort0.write(inByte);
				ui->blinkCancelButton();
				//dataFile.print(inByte);
			}
			if (serialPort0.available()) {
				int inByte = serialPort0.read();
				serialPort3.write(inByte);
				ui->blinkOKButton();
				//dataFile.print(inByte);
			}
			break;
		case 1: // db9_null
			if (serialPort2.available()) {
				int inByte = serialPort2.read();
				serialPort0.write(inByte);
				ui->blinkCancelButton();
				//dataFile.print(inByte);
			}
			if (serialPort0.available()) {
				int inByte = serialPort0.read();
				serialPort2.write(inByte);
				ui->blinkOKButton();
				//dataFile.print(inByte);
			}
			break;
		case 2: // cisco
			if (serialPort1.available()) {
				int inByte = serialPort1.read();
				serialPort0.write(inByte);
				ui->blinkCancelButton();
				//dataFile.print(inByte);
			}
			if (serialPort0.available()) {
				int inByte = serialPort0.read();
				serialPort1.write(inByte);
				ui->blinkOKButton();
				//dataFile.print(inByte);
		}
			break;
	}

	// Flush data written to log file
	//dataFile.sync();
}
