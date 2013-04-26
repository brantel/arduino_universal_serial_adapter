/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
 by: Mike Crosson
 Nusku Networks
 date: 2013/03/09
 license: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute.
 */

#ifndef UILCD_h
#define UILCD_h

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SdFile.h>
#include <SPI.h>

#include "Project.h"
#include "UIJoystickPSP.h"
#include "Config.h"

// Forward declaration of Config
class Config;

// Use global config and ui objects defined / initialized in main ino file
extern Config* config;

#define BUFFPIXEL 20

enum screen {
	splashScreen,
	mainScreen,
	connectionScreen,
	lineSpeedScreen,
	voltageScreen,
	timeoutscreen
};

class UILCD {
private:
	Adafruit_ST7735* tft;

	int currentLine;
	screen currentScreen;

	uint32_t read32(SdFile f);
	uint16_t read16(SdFile f);

	void drawSplashScreen();
	void drawMainScreen();
	void drawConnectionScreen(bool keepCurrentLine);
	void drawLineSpeedScreen(bool keepCurrentLine);
	void drawVoltageScreen(bool keepCurrentLine);
	void drawTimeoutScreen(bool keepCurrentLine);
	void hilightLine(int line);
	void unHilightLine(int line);
	void mainScreenHilight(joyDirection direction);
	void configScreenHighlight(joyDirection direction);
	void mainScreenOkButton();
	void mainScreenCancelButton();

public:
	UILCD();
	void bmpDraw(char *filename, uint8_t x, uint8_t y);
	void handleJoystickEvent(joyDirection aDirection);
	void handleOkButtonEvent();
	void handleCancelButtonEvent();
	void turnOff();
	void turnOn();
	void start();
};

#endif
