
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
  none=-1
};

// Map a mode -> text value
char* modeToText[] = {
  "Phone UART",
  "DB9 - Normal",
  "DB9 - Null Mdm",
  "Cisco console"
};

// Mode info needed
serialmode currentMode = none;
serialmode selectedMode = none;

// Printing text
void printMode(serialmode aMode);
void setMode(serialmode aMode);
void setSelection(serialmode aMode);

// Defaults
void setDefaults() {
  setMode(phone);
  setSelection(phone);
}

// Figure out offsets
int xLoc(int toSkip) { // Physically -- vertical
  return (CHAR_HEIGHT * toSkip) + (CHAR_HEIGHT / 2);
}
int yLoc (int toSkip) { // Physical -- horizontal
  return (CHAR_WIDTH * toSkip) + (CHAR_WIDTH / 2);
}

