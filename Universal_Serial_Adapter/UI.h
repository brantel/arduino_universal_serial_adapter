/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
  by: Mike Crosson
  Nusku Networks
  date: 2013/03/09
  license: CC-BY SA 3.0 - Creative commons share-alike 3.0
  use this code however you'd like, just keep this license and
  attribute.
*/

// Font sizes
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16

void setLineSpeed(linespeed aLineSpeed);
void setMode(serialmode aMode);
void setSelection(serialmode aMode);

void printTitles();
void printMode(serialmode aMode);
void printLineSpeed(linespeed aLineSpeed, bool selected);
void printRx(bool show);
void printTx(bool show);

int xLoc(float toSkip);
int yLoc (float toSkip);

