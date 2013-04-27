/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
 by: Mike Crosson
 Nusku Networks
 date: 2013/03/09
 license: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute.
 */

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SdFile.h>
#include <SPI.h>

#include "Project.h"
#include "UILCD.h"
#include "UIJoystickPSP.h"

UILCD::UILCD() {
  #if DEBUG == 2
    serialPort0.println("UILCD::UILCD()");
  #endif

  pinMode(LCD_LITE, OUTPUT);

	tft = new Adafruit_ST7735(LCD_CS, LCD_DC, LCD_RST);
	tft->initR(INITR_BLACKTAB);
	tft->setRotation(3);
}

void UILCD::start() {
#if DEBUG == 2
    serialPort0.println("UILCD::start()");
#endif
  drawSplashScreen();
  drawMainScreen();
}

void UILCD::turnOn() {
#if DEBUG == 2
    serialPort0.println("UILCD::turnOn()");
#endif
  digitalWrite(LCD_LITE, HIGH);
}

void UILCD::turnOff() {
#if DEBUG == 2
    serialPort0.println("UILCD::turnOff()");
#endif
  digitalWrite(LCD_LITE, LOW);
}

void UILCD::handleJoystickEvent(joyDirection direction) {
#if DEBUG == 2
    serialPort0.println("UILCD::handleJoystickEvent()");
    serialPort0.println("begin UILCD::handleJoystickEvent");
    serialPort0.print("Current Screen: ");
    serialPort0.println(currentScreen);
#endif

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
#if DEBUG == 2
    serialPort0.println("UILCD::handleOkButtonEvent()");
    serialPort0.println("begin UILCD::handleOkButtonEvent");
    serialPort0.print("Current Screen: ");
    serialPort0.println(currentScreen);
#endif

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
#if DEBUG == 2
    serialPort0.println("UILCD::handleCancelButtonEvent");
    serialPort0.println("begin UILCD::handleCancelButtonEvent");
    serialPort0.print("Current Screen: ");
    serialPort0.println(currentScreen);
#endif

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
#if DEBUG == 2
    serialPort0.println("UILCD::mainScreenOkButton");
#endif
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
#if DEBUG == 2
    serialPort0.println("UILCD::mainScreenCancelButton()");
#endif
  // Do nothing for now
}

void UILCD::unHilightLine(int line) {
#if DEBUG == 2
    serialPort0.println("UILCD::unHilightLine()");
#endif
  tft->setCursor(0, line * FONT_HEIGHT);
  tft->fillRect(0, line * FONT_HEIGHT, FONT_WIDTH, FONT_HEIGHT, BACKGROUND);
}

void UILCD::hilightLine(int line) {
#if DEBUG == 2
    serialPort0.println("UILCD::hilightLine()");
#endif
  tft->setCursor(0, line * FONT_HEIGHT);
  tft->setTextColor(HILIGHT);
  tft->print("*");
}

void UILCD::mainScreenHilight(joyDirection direction) {
#if DEBUG == 2
    serialPort0.println("UILCD::mainScreenHilight()");
#endif
  if (direction == joyUp) {
    // Don't go up past the 1st line
    if (currentLine == 0) {
      return;
    }
    unHilightLine(currentLine);

    currentLine -= 1;

    // Skip blank lines
    if (config->getSerialMode() == ttl) {
#if DEBUG == 2
        serialPort0.println("Serial ttl blank line skip");
#endif
      if (currentLine == 3 || currentLine == 6) {
        currentLine -= 1;
      }
    }
    else {
#if DEBUG == 2
        serialPort0.println("Non-serial ttl blank line skip");
#endif
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
#if DEBUG == 2
        serialPort0.println("Serial ttl blank line skip");
#endif
      if (currentLine == 3 || currentLine == 6) {
        currentLine += 1;
      }
    }
    else {
#if DEBUG == 2
        serialPort0.println("Non-serial ttl blank line skip");
#endif
      if (currentLine == 2 || currentLine == 5) {
        currentLine += 1;
      }
    }

    hilightLine(currentLine);
  }
}

void UILCD::configScreenHighlight(joyDirection direction) {
#if DEBUG == 2
    serialPort0.println("UILCD::configScreenhilight()");
#endif
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
#if DEBUG == 2
    serialPort0.println("UILCD::drawTimeoutScreen()");
#endif
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
#if DEBUG == 2
    serialPort0.println("UILCD::drawConnectionScreen()");
#endif
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
#if DEBUG == 2
    serialPort0.println("UILCD::drawLineSpeedScreen()");
#endif
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
#if DEBUG == 2
    serialPort0.println("UILCD::drawVoltageScreen()");
#endif
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
#if DEBUG == 2
    serialPort0.println("UILCD::drawMainScreen()");
#endif
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
#if DEBUG == 2
    serialPort0.println("UILCD::drawSplashScreen()");
#endif
  tft->setCursor(0,0);
	tft->fillScreen(SPLASH_BACKGROUND);
	bmpDraw(splashScreenFileName, 13, 0);
  delay(1250);
  for (int16_t y=0; y < tft->height(); y+=1) {
    tft->drawFastHLine(0, y, tft->width(), BACKGROUND);
    delay(10);
  }
}

void UILCD::bmpDraw(char *filename, uint8_t x, uint8_t y) {
  #if DEBUG == 2
    serialPort0.println("UILCD::bmpDraw()");
  #endif
  
  SdFile   bmpFile;
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

  if((x >= tft->width()) || (y >= tft->height())) {
    return;
  }

  #if DEBUG >= 1
    serialPort0.println();
    serialPort0.print("Loading image '");
    serialPort0.print(filename);
    serialPort0.println('\'');
  #endif

  // Open requested file on SD card
  if (!bmpFile.open(filename, O_READ)) {
    serialPort0.print(filename);
    serialPort0.println(" not found");
    return;
  }

  // Parse BMP header
  if(read16(&bmpFile) == 0x4D42) { // BMP signature
    uint32_t fileSize = read32(&bmpFile);
    #if DEBUG == 2
      serialPort0.print("File size: "); 
      serialPort0.println(fileSize);
    #endif
    
    (void)read32(&bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(&bmpFile); // Start of image data

    #if DEBUG == 2
      serialPort0.print("Image Offset: "); 
      serialPort0.println(bmpImageoffset, DEC);
    #endif

    // Read DIB header
    float headerSize = read32(&bmpFile);

    #if DEBUG == 2
      serialPort0.print("Header size: "); 
      serialPort0.println(headerSize);
    #endif

    bmpWidth  = read32(&bmpFile);
    bmpHeight = read32(&bmpFile);
    if(read16(&bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(&bmpFile); // bits per pixel
      #if DEBUG >= 1
        serialPort0.print("Bit Depth: "); 
        serialPort0.println(bmpDepth);
      #endif
      if((bmpDepth == 24) && (read32(&bmpFile) == 0)) { // 0 = uncompressed
        goodBmp = true; // Supported BMP format -- proceed!
        #if DEBUG >= 1
          serialPort0.print("Image size: ");
          serialPort0.print(bmpWidth);
          serialPort0.print('x');
          serialPort0.println(bmpHeight);
        #endif

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
        if((x+w-1) >= tft->width()) {
          w = tft->width()  - x;
        }
        if((y+h-1) >= tft->height()) {
          h = tft->height() - y;
        }

        // Set TFT address window to clipped image bounds
        tft->setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) { // For each scanline...

          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) { // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          }
          else {    // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          }
          if(bmpFile.curPosition() != pos) { // Need seek?
            bmpFile.seekSet(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each pixel...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              bmpFile.read(&sdbuffer, sizeof(sdbuffer));
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
        #if DEBUG == 2
          serialPort0.print("Loaded in ");
          serialPort0.print(millis() - startTime);
          serialPort0.println(" ms");
        #endif
      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp) {
    serialPort0.println("BMP format not recognized.");
  }
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t UILCD::read16(SdFile* f) {
//#if DEBUG == 2
//    serialPort0.println("UILCD::read16()");
//#endif
  uint16_t result;
  int numBytesRead = f->read(&result, sizeof(result));
  return result;
}

uint32_t UILCD::read32(SdFile* f) {
//#if DEBUG == 2
//    serialPort0.println("UILCD::read32()");
//#endif
  uint32_t result;
  int numBytesRead = f->read(&result, sizeof(result));
  return result;
}
