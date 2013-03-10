/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
  by: Mike Crosson
  Nusku Networks
  date: 2013/03/09
  license: CC-BY SA 3.0 - Creative commons share-alike 3.0
  use this code however you'd like, just keep this license and
  attribute.
  
  This sketch currently only shows the four serial modes and
  uses S1-S3 to select the current mode.
  
  A trailing * after the mode indicates the current mode
  
  Button Map:
    S1: Up
    S2: Select/Enter
    S3: Down
  
  Serial Modes:
    Phone UART
    DB9 Normal
    DB9 Null Modem
    Cisco console
*/

// LCD
LCDShield lcd;   // Line length max is 16

// Buttons
int buttonPins[3] = {3, 4, 5};

// Standard colors
#define BACKGROUND  BLACK
#define TEXT        GRAY
#define HILIGHT     GOLD

// Font sizes
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16

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
char* modeToText[] = {
  "Phone UART",
  "DB9 - Normal",
  "DB9 - Null Mdm",
  "Cisco console"
};

// Line speeds supported
//  Abused in for loops / lookup talbes -- DO NOT CHANGE none or set values
enum linespeed {
  twentyFourHundredBaud,
  ninetySixHundredBaud,
  nineteenTwoK,
  thirtyeightFourK,
  fiftysevenFiveK,
  oneNineteenTwoK,
  zero=-1
};

// Description / speed scruct to use in lookup table
struct linespeedinfo {
  char description[8];
  int linespeed;
};

// Known and supported line speeds
linespeedinfo linespeeds[] = {
  {"2400b", 2400},
  {"9600b", 9600},
  {"19.2k", 19200},
  {"38.4k", 38400},
  {"57.5k", 57600},
  {"115k", 115200}
};

// Mode info needed
serialmode currentMode = none;
serialmode selectedMode = none;
linespeed currentLineSpeed = zero;

// Printing text
void printMode(serialmode aMode);
void printLineSpeed(linespeedinfo linespeed);

// Various sets for mode/selection/linespeed
void setMode(serialmode aMode);
void setSelection(serialmode aMode);
void setLineSpeed(linespeed aLineSpeed);

// Figure out offsets for text printing
int xLoc(float toSkip) { // Physically -- vertical
  return (CHAR_HEIGHT * toSkip) + (CHAR_HEIGHT / 2);
}
int yLoc (float toSkip) { // Physical -- horizontal
  return (CHAR_WIDTH * toSkip) + (CHAR_WIDTH / 2);
}



