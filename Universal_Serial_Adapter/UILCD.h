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

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SD.h>
#include <SPI.h>

#include "Project.h"
#include "UIJoystickPSP.h"

#ifndef UILCD_h
#define UILCD_h

#define BUFFPIXEL 20

enum screen {
	splashScreen,
	mainScreen
};

class UILCD {
private:
	Adafruit_ST7735* tft;

	int previousLine;
	screen currentScreen;

	uint32_t read32(File f);
	uint16_t read16(File f);

	void splashScreen();
	void mainScreen();
	void hilightLine(int line);
	void unHilightLine(int line);
	void mainScreenHilight(joyDirection direction);

public:
	UILCD();
	void bmpDraw(char *filename, uint8_t x, uint8_t y);
	void startUI();
	void handleJoystickEvent(joyDirection aDirection);
};

#endif
