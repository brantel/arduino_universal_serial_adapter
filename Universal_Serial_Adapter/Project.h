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

// Pinout / things that need configuration
#define okButtonPin     23
#define okButtonLed     22
#define cancelButtonPin 25
#define cancelButtonLed 24
#define pspXPin         0 // After GND / @ edge
#define pspYPin         1 // Between VCC and gnd

// Don't change anything below here
// -----------------------------------------------------------------------------

// Serial modes supported
//  Abused in for loops / lookup tables -- DO NOT CHANGE none or set values
enum serialmode { 
  phone,
  db9_norm, 
  db9_null, 
  cisco,
  modelinespeed,
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

// Description / speed scruct to use in lookup table
struct linespeedinfo {
  char* description;
  int linespeed;
};

// Known and supported line speeds
extern linespeedinfo linespeeds[];

// Mode info needed
extern serialmode currentMode;
extern serialmode selectedMode;
extern linespeed currentLineSpeed;

#endif
