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
#include "UILCD.h"
#include "UIJoystickPSP.h"

UILCD::UILCD(Config* config) {
  if (DEBUG) {
    Serial.println("UILCD::UILCD()");
  }
  pinMode(LCD_LITE, OUTPUT);

  this->config = config;

	tft = new Adafruit_ST7735(LCD_CS, LCD_DC, LCD_RST);
	tft->initR(INITR_BLACKTAB);
	tft->setRotation(3);

	if (!SD.begin(SD_CS) && DEBUG) {
		Serial.println("SD.begin(SD_CS) -- failed!");
	}
}

void UILCD::start() {
  if (DEBUG) {
    Serial.println("UILCD::start()");
  }
  drawSplashScreen();
  drawMainScreen();
}

void UILCD::turnOn() {
  if (DEBUG) {
    Serial.println("UILCD::turnOn()");
  }
  digitalWrite(LCD_LITE, HIGH);
}

void UILCD::turnOff() {
  if (DEBUG) {
    Serial.println("UILCD::turnOff()");
  }
  digitalWrite(LCD_LITE, LOW);
}

void UILCD::handleJoystickEvent(joyDirection direction) {
  if (DEBUG) {
    Serial.println("UILCD::handleJoystickEvent()");
    Serial.println("begin UILCD::handleJoystickEvent");
    Serial.print("Current Screen: ");
    Serial.println(currentScreen);
  }

  switch (currentScreen) {
    case 1: // enum screen -> mainScreen
      mainScreenHilight(direction);
      break;
    default: // config screens
      configScreenHighlight(direction);
      break;
  }
}

void UILCD::handleOkButtonEvent() {
  if (DEBUG) {
    Serial.println("UILCD::handleOkButtonEvent()");
    Serial.println("begin UILCD::handleOkButtonEvent");
    Serial.print("Current Screen: ");
    Serial.println(currentScreen);
  }

  switch (currentScreen) {
    case 1: // enum screen -> mainScreen
      mainScreenOkButton();
      break;
    case 2: // connectionScreen
      config->setMode((serialmode)(currentLine - 3));
      drawConnectionScreen(true);
      break;
    case 3: // lineSpeedScreen
      config->setLineSpeed((linespeed)(currentLine - 3));
      drawLineSpeedScreen(true);
      break;
    case 4: // voltageScreen
      config->setVoltage((ttlvoltage)(currentLine - 3));
      drawVoltageScreen(true);
      break;
    case 5: // timeoutScreen
      config->setLCDTimeout((timeout)(currentLine - 3));
      drawTimeoutScreen(true);
      break;
  }
}

void UILCD::handleCancelButtonEvent() {
  if (DEBUG) {
    Serial.println("UILCD::handleCancelButtonEvent");
    Serial.println("begin UILCD::handleCancelButtonEvent");
    Serial.print("Current Screen: ");
    Serial.println(currentScreen);
  }

  switch (currentScreen) {
    case 1: // enum screen -> mainScreen
      mainScreenCancelButton();
      break;
    default:
      drawMainScreen();
      break;
  }
}

void UILCD::mainScreenOkButton() {
  if (DEBUG) {
    Serial.println("UILCD::mainScreenOkButton");
  }
  switch(currentLine) {
    case 0: // Connection Type
      drawConnectionScreen(false);
      break;
    case 1: // Line speed
      drawLineSpeedScreen(false);
      break;
    case 2: // Voltage
      drawVoltageScreen(false);
      break;
    // case 4: // start data log
    //   break;
    // case 5: // view serial data
    //   break;
    // case 7: // configure rtc
    //   break;
    case 8:
      drawTimeoutScreen(false);
      break;
  }
}

void UILCD::mainScreenCancelButton() {
  if (DEBUG) {
    Serial.println("UILCD::mainScreenCancelButton()");
  }
  // Do nothing for now
}

void UILCD::unHilightLine(int line) {
  if (DEBUG) {
    Serial.println("UILCD::unHilightLine()");
  }
  tft->setCursor(0, line * FONT_HEIGHT);
  tft->fillRect(0, line * FONT_HEIGHT, FONT_WIDTH, FONT_HEIGHT, BACKGROUND);
}

void UILCD::hilightLine(int line) {
  if (DEBUG) {
    Serial.println("UILCD::hilightLine()");
  }
  tft->setCursor(0, line * FONT_HEIGHT);
  tft->setTextColor(HILIGHT);
  tft->print("*");
}

void UILCD::mainScreenHilight(joyDirection direction) {
  if (DEBUG) {
    Serial.println("UILCD::mainScreenHilight()");
  }
  if (direction == joyUp) {
    // Don't go up past the 1st line
    if (currentLine == 0) {
      return;
    }
    unHilightLine(currentLine);

    currentLine -= 1;

    // Skip blank lines
    if (config->getSerialMode() == ttl) {
      if (DEBUG) {
        Serial.println("Serial ttl blank line skip");
      }
      if (currentLine == 3 || currentLine == 6) {
        currentLine -= 1;
      }
    }
    else {
      if (DEBUG) {
        Serial.println("Non-serial ttl blank line skip");
      }
      if (currentLine == 2 || currentLine == 5) {
        currentLine -= 1;
      }
    }

    hilightLine(currentLine);
  }

  if (direction == joyDown) {
    // Don't go past the last line
    if (config->getSerialMode() == ttl) {
      if (currentLine == 8) {
        return;
      }
    }
    else {
      if (currentLine == 7) {
        return;
      }
    }
    unHilightLine(currentLine);

    currentLine += 1;

    // Skip blank lines
    if (config->getSerialMode() == ttl) {
      if (DEBUG) {
        Serial.println("Serial ttl blank line skip");
      }
      if (currentLine == 3 || currentLine == 6) {
        currentLine += 1;
      }
    }
    else {
      if (DEBUG) {
        Serial.println("Non-serial ttl blank line skip");
      }
      if (currentLine == 2 || currentLine == 5) {
        currentLine += 1;
      }
    }

    hilightLine(currentLine);
  }
}

void UILCD::configScreenHighlight(joyDirection direction) {
  if (DEBUG) {
    Serial.println("UILCD::configScreenhilight()");
  }
  if (direction == joyUp) {
    // Don't go up past the 1st line
    if (currentLine == 3) {
      return;
    }
    unHilightLine(currentLine);

    currentLine -= 1;

    hilightLine(currentLine);
  }

  if (direction == joyDown) {
    // Don't go past the last line
    switch (currentScreen) {
      case 2: // connectionScreen
        if (currentLine == maxserialmode + 2) {
          return;
        }
        break;
      case 3: // lineSpeedScreen
        if (currentLine == maxlinespeed + 2) {
          return;
        }
        break;
      case 4: // voltageScreen
        if (currentLine == maxvoltage + 2) {
          return;
        }
        break;
      case 5: // timeoutScreen
        if (currentLine == maxtimeout + 2) {
          return;
        }
        break;
    }

    unHilightLine(currentLine);

    currentLine += 1;

    hilightLine(currentLine);
  }
}

void UILCD::drawTimeoutScreen(bool keepCurrentLine) {
  if (DEBUG) {
    Serial.println("UILCD::drawTimeoutScreen()");
  }
  currentScreen = timeoutscreen;
  if (!keepCurrentLine) {
    currentLine = 3;
  }

  tft->setCursor(0,0);
  tft->fillScreen(BACKGROUND);
  tft->setTextColor(TEXT);
  tft->setTextWrap(true);

  tft->println("Timout selection");
  tft->println("  Current value is yellow");
  tft->println();

  for (int i=0; i<maxtimeout; i++) {
    if (config->getTimeout() == i) {
      tft->setTextColor(HILIGHT);
    }
    tft->print(" ");
    tft->println(timeoutToText[i]);
    tft->setTextColor(TEXT);
  }

  if (keepCurrentLine) {
    hilightLine(currentLine);
  }
  else {
    hilightLine(3);
  }
}

void UILCD::drawConnectionScreen(bool keepCurrentLine) {
  if (DEBUG) {
    Serial.println("UILCD::drawConnectionScreen()");
  }
  currentScreen = connectionScreen;
  if (!keepCurrentLine) {
    currentLine = 3;
  }

  tft->setCursor(0,0);
  tft->fillScreen(BACKGROUND);
  tft->setTextColor(TEXT);
  tft->setTextWrap(true);

  tft->println("Type Selection");
  tft->println("  Current value is yellow");
  tft->println();

  for (int i=0; i<maxserialmode; i++) {
    if (config->getSerialMode() == i) {
      tft->setTextColor(HILIGHT);
    }
    tft->print(" ");
    tft->println(modeToText[i]);
    tft->setTextColor(TEXT);
  }

  if (keepCurrentLine) {
    hilightLine(currentLine);
  }
  else {
    hilightLine(3);
  }
}

void UILCD::drawLineSpeedScreen(bool keepCurrentLine) {
  if (DEBUG) {
    Serial.println("UILCD::drawLineSpeedScreen()");
  }
  currentScreen = lineSpeedScreen;
  if (!keepCurrentLine) {
    currentLine = 3;
  }

  tft->setCursor(0,0);
  tft->fillScreen(BACKGROUND);
  tft->setTextColor(TEXT);
  tft->setTextWrap(true);

  tft->println("Speed Selection");
  tft->println("  Current value is yellow");
  tft->println();

  for (int i=0; i<maxlinespeed; i++) {
    if (config->getLineSpeed() == i) {
      tft->setTextColor(HILIGHT);
    }
    tft->print(" ");
    tft->println(linespeeds[i].description);
    tft->setTextColor(TEXT);
  }

  if (keepCurrentLine) {
    hilightLine(currentLine);
  }
  else {
    hilightLine(3);
  }
}

void UILCD::drawVoltageScreen(bool keepCurrentLine) {
  if (DEBUG) {
    Serial.println("UILCD::drawVoltageScreen()");
  }
  currentScreen = voltageScreen;
  if (!keepCurrentLine) {
    currentLine = 3;
  }

  tft->setCursor(0,0);
  tft->fillScreen(BACKGROUND);
  tft->setTextColor(TEXT);
  tft->setTextWrap(true);

  tft->println("Voltage Selection");
  tft->println("  Current value is yellow");
  tft->println();

  for (int i=0; i<maxvoltage; i++) {
    if (config->getVoltage() == i) {
      tft->setTextColor(HILIGHT);
    }
    tft->print(" ");
    tft->println(voltageToText[i]);
    tft->setTextColor(TEXT);
  }

  if (keepCurrentLine) {
    hilightLine(currentLine);
  }
  else {
    hilightLine(3);
  }
}

void UILCD::drawMainScreen() {
  if (DEBUG) {
    Serial.println("UILCD::drawMainScreen()");
  }
  currentScreen = mainScreen;
  currentLine = 0;

  tft->setCursor(0,0);
  tft->fillScreen(BACKGROUND);
  tft->setTextColor(TEXT);
  tft->setTextWrap(true);
  
  tft->print(" Con Typ: ");
  tft->println(modeToText[config->getSerialMode()]); // TODO: This should be pulled from the config
  tft->print(" Line Speed: ");
  tft->println(linespeeds[config->getLineSpeed()].description);
  if (config->getSerialMode() == ttl) {
    tft->print(" Voltage (TTL Only): ");
    tft->println(voltageToText[config->getVoltage()]);
  }
  
  tft->println();
  tft->println(" Start data logging");
  tft->println(" View serial data");
  
  tft->println();
  tft->println(" Configure RTC / Clock");
  tft->println(" Configure timeout");

  hilightLine(0);
}

void UILCD::drawSplashScreen() {
  if (DEBUG) {
    Serial.println("UILCD::drawSplashScreen()");
  }
  tft->setCursor(0,0);
	tft->fillScreen(SPLASH_BACKGROUND);
	bmpDraw("splash.bmp", 13, 0);
  delay(1250);
  for (int16_t y=0; y < tft->height(); y+=1) {
    tft->drawFastHLine(0, y, tft->width(), BACKGROUND);
    delay(10);
  }
}

void UILCD::bmpDraw(char *filename, uint8_t x, uint8_t y) {
  if (DEBUG) {
    Serial.println("UILCD::bmpDraw()");
  }
  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  if((x >= tft->width()) || (y >= tft->height())) return;

  if (DEBUG) {
    Serial.println();
    Serial.print("Loading image '");
    Serial.print(filename);
    Serial.println('\'');
  }

  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    if (DEBUG) {
      Serial.print("File not found");
    }
    return;
  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    if (DEBUG) {
      Serial.print("File size: "); 
      Serial.println(read32(bmpFile));
    }
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    if (DEBUG) {
      Serial.print("Image Offset: "); 
      Serial.println(bmpImageoffset, DEC);
    }
    // Read DIB header
    if (DEBUG) {
      Serial.print("Header size: "); 
      Serial.println(read32(bmpFile));
    }
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      if (DEBUG) {
        Serial.print("Bit Depth: "); 
        Serial.println(bmpDepth);
      }
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        if (DEBUG) {
          Serial.print("Image size: ");
          Serial.print(bmpWidth);
          Serial.print('x');
          Serial.println(bmpHeight);
        }

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft->width())  w = tft->width()  - x;
        if((y+h-1) >= tft->height()) h = tft->height() - y;

        // Set TFT address window to clipped image bounds
        tft->setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) { // For each scanline...

          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
          pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each pixel...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format, push to display
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft->pushColor(tft->Color565(r,g,b));
          } // end pixel
          delay(5);
        } // end scanline
        if (DEBUG) {
          Serial.print("Loaded in ");
          Serial.print(millis() - startTime);
          Serial.println(" ms");
        }
      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp && DEBUG) Serial.println("BMP format not recognized.");
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t UILCD::read16(File f) {
  if (DEBUG) {
    Serial.println("UILCD::read16()");
  }
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t UILCD::read32(File f) {
  if (DEBUG) {
    Serial.println("UILCD::read32()");
  }
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}
