/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
  by: Mike Crosson
  Nusku Networks
  date: 2013/03/09
  license: CC-BY SA 3.0 - Creative commons share-alike 3.0
  use this code however you'd like, just keep this license and
  attribute.
*/

#include <SerialPort.h>
#include <SdFat.h>

#ifndef Project_h
#define Project_h

#define DEBUG 1 // NONE = 0; MINIMAL = 1; FULL = 2;

// Whether or not the Arduino DUE is used as the base board
// Assume Mega 2560 otherwise
#define ARD_DUE false

// Buttons / Joystick / Input Hardware Pinouts
#define okButtonPin     22
#define okButtonLed     23
#define cancelButtonPin 24
#define cancelButtonLed 25
#define pspXPin         0 // After GND / @ edge
#define pspYPin         1 // Between VCC and gnd

// LCD Pinout
#define LCD_LITE 26 // Backlight pin
#define SD_CS    7  // Chip select line for SD card
#define LCD_CS  53  // Chip select line for TFT display
#define LCD_DC   9  // Data/command line for TFT
#define LCD_RST  8  // Reset line for TFT (or connect to +5V)

// Voltage Pinouts
#define voltagePinOnePointEight   40 // Pin controlling 1.8V TTL logic
#define voltagePinThreePointThree 41 // Pin controlling 3.3V TTL logic
#define voltagePinFivePointZero   42 // Pin controlling 5V TTL logic

// Timer pins
#define timerThreePin 2 // Maps to Mega pin 12

// Splash screen related
#define splashScreenFileName "SPLASH.BMP"

// SPI SD Card speed (Set to HALF for breadboards, full for better performance)
#define SPI_PROJECT_SPEED SPI_HALF_SPEED

// Colors / theme of UI
#define SPLASH_BACKGROUND ST7735_WHITE
#define BACKGROUND        ST7735_BLACK
#define TEXT              ST7735_WHITE
#define HILIGHT           ST7735_YELLOW

// Don't change anything below here
// -----------------------------------------------------------------------------

// Global SD card so LCD / config can read/write files
extern SdFat sd;

#define FONT_WIDTH  6
#define FONT_HEIGHT 8

// Serial ports
#if ARD_DUE
extern SerialPort<0, 4096, 4096> serialPort0;
extern SerialPort<1, 4096, 4096> serialPort1;
extern SerialPort<2, 4096, 4096> serialPort2;
extern SerialPort<3, 4096, 4096> serialPort3;
#else
extern SerialPort<0, 512, 512> serialPort0;
extern SerialPort<1, 512, 512> serialPort1;
extern SerialPort<2, 512, 512> serialPort2;
extern SerialPort<3, 512, 512> serialPort3;
#endif

// Serial modes supported
//  Abused in for loops / lookup tables -- DO NOT CHANGE none or set values
enum serialmode { 
  ttl,
  db9_null, 
  cisco,
  maxserialmode,
  none=-1
};

// Map a mode -> text value
extern char* modeToText[];

// Line speeds supported
//  Abused in for loops / lookup talbes -- DO NOT CHANGE none or set values
enum linespeed {
  twentyFourHundredBaud,
  ninetySixHundredBaud,
  nineteenTwoK,
  thirtyeightFourK,
  fiftysevenFiveK,
  oneFifteenTwoK,
  maxlinespeed,
  zero=-1
};

enum ttlvoltage {
  onePointEight,
  threePointThree,
  five,
  maxvoltage,
  negOne=-1
};

extern char* voltageToText[];

// Description / speed scruct to use in lookup table
struct linespeedinfo {
  char* description;
  int linespeed;
};

// Known and supported line speeds
extern linespeedinfo linespeeds[];

enum timeout {
  tenseconds,
  thirtyseconds,
  oneminute,
  fiveminutes,
  never,
  maxtimeout
};

extern char* timeoutToText[];

#endif
