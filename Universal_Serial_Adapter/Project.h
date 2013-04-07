/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
  by: Mike Crosson
  Nusku Networks
  date: 2013/03/09
  license: CC-BY SA 3.0 - Creative commons share-alike 3.0
  use this code however you'd like, just keep this license and
  attribute.
*/

#ifndef Project_h
#define Project_h

#define DEBUG true // For controlling debug output via serial

// Pinout / things that need configuration
#define okButtonPin     22
#define okButtonLed     23
#define cancelButtonPin 24
#define cancelButtonLed 25
#define pspXPin         0 // After GND / @ edge
#define pspYPin         1 // Between VCC and gnd
// LCD Pinouts
#define SD_CS    7  // Chip select line for SD card
#define LCD_CS  53  // Chip select line for TFT display
#define LCD_DC   9  // Data/command line for TFT
#define LCD_RST  8  // Reset line for TFT (or connect to +5V)

#define SPLASH_BACKGROUND ST7735_WHITE
#define BACKGROUND        ST7735_BLACK
#define TEXT              ST7735_WHITE
#define HILIGHT           ST7735_YELLOW

// Don't change anything below here
// -----------------------------------------------------------------------------

#define FONT_WIDTH  6
#define FONT_HEIGHT 8

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
  oneNineteenTwoK,
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
