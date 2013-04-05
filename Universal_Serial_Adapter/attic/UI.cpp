/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
  by: Mike Crosson
  Nusku Networks
  date: 2013/03/09
  license: CC-BY SA 3.0 - Creative commons share-alike 3.0
  use this code however you'd like, just keep this license and
  attribute.
*/

#include <Arduino.h>

#include "Project.h"
#include "UI.h"

// Figure out offsets for text printing
int xLoc(float toSkip) { // Physically -- vertical
  return (CHAR_HEIGHT * toSkip) + (CHAR_HEIGHT / 2);
}
int yLoc (float toSkip) { // Physical -- horizontal
  return (CHAR_WIDTH * toSkip) + (CHAR_WIDTH / 2);
}

void setLineSpeed(linespeed aLineSpeed) {
  if (aLineSpeed >= maxlinespeed) {
    currentLineSpeed = (linespeed)0;
  }
  else {
    currentLineSpeed = aLineSpeed;
  }
  bool sel = selectedMode == modelinespeed ? true : false;
  printLineSpeed(currentLineSpeed, sel);
}

void setMode(serialmode aMode) {
  if (aMode != modelinespeed) {
    serialmode previousMode = currentMode;
    currentMode = aMode;
    
    lcd.setStr(" ", xLoc(previousMode), yLoc(0), TEXT, BACKGROUND);
    lcd.setStr("*", xLoc(currentMode), yLoc(0), TEXT, BACKGROUND);
  }
  else {
    setLineSpeed((linespeed)(currentLineSpeed + 1));
  }
}

void setSelection(serialmode aMode) {
  serialmode previousSelection = selectedMode;
  selectedMode = aMode;
  
  int yLocOne = yLoc(1);
  
  int xSelected = 0;
  if (selectedMode != modelinespeed) {
    xSelected = xLoc(selectedMode) + CHAR_HEIGHT;
  }
  
  int xPrevious = 0;
  if (previousSelection != modelinespeed) {
    xPrevious = xLoc(previousSelection) + CHAR_HEIGHT;
  }

  int previousLength = 0;
  if (previousSelection != modelinespeed) {
    previousLength = strlen(modeToText[previousSelection]) * CHAR_WIDTH;
  }
  
  int selectedLength = 0;
  if (selectedMode != modelinespeed) {
    selectedLength = strlen(modeToText[selectedMode]) * CHAR_WIDTH;
  }
  
  if (selectedMode != modelinespeed) {
    lcd.setLine(xSelected, yLocOne, xSelected, yLocOne + selectedLength, HILIGHT);
  }
  else {
    printLineSpeed(currentLineSpeed, true);
  }
  
  if (previousSelection != modelinespeed) {
    lcd.setLine(xPrevious, yLocOne, xPrevious, yLocOne + previousLength, BACKGROUND);
  }
  else {
    printLineSpeed(currentLineSpeed, false);
  }
}

void printTitles() {
  lcd.setStr(" RX  Ln Spd  Tx ", xLoc(5), 0, TEXT, BACKGROUND);
}

void printMode(serialmode aMode) {
  lcd.setStr(modeToText[aMode], xLoc(aMode), yLoc(1), TEXT, BACKGROUND);
}

void printLineSpeed(linespeed aLineSpeed, bool selected) {
  int xPosText = xLoc(6);
  int yPosText = yLoc(5);
  
  int xPosLine = xLoc(7);
  int yPosLine = yLoc(5);
  
  char* toPrint = linespeeds[aLineSpeed].description;
  int length = strlen(toPrint);
  
  lcd.setStr("       ", xPosText, yPosText, BACKGROUND, BACKGROUND);
  lcd.setLine(xPosLine, yPosLine, xPosLine, yPosLine + 7 * CHAR_WIDTH, BACKGROUND);

  lcd.setStr(toPrint, xPosText, yPosText, TEXT, BACKGROUND);
  if (selected) {
    lcd.setLine(xPosLine, yPosLine, xPosLine, yPosLine + length * CHAR_WIDTH, HILIGHT);
  }
}

void printRx(bool show) {
  int vertXPosStart = xLoc(6.25);
  int vertYPosStart = yLoc(1.5);
  int vertXPosEnd = xLoc(7.25);
  int vertYPosEnd = yLoc(1.5);

  int lftXPosStart = vertXPosEnd;
  int lftYPosStart = vertYPosStart;
  int lftXPosEnd = vertXPosStart + (CHAR_HEIGHT / 2);
  int lftYPosEnd = vertYPosStart - CHAR_WIDTH;

  int rtXPosStart = vertXPosEnd;
  int rtYPosStart = vertYPosStart;
  int rtXPosEnd = vertXPosStart + (CHAR_HEIGHT / 2);
  int rtYPosEnd = vertYPosStart + CHAR_WIDTH;

  int color = show ? EMERALD : BACKGROUND;

  lcd.setLine(vertXPosStart, vertYPosStart, vertXPosEnd, vertYPosEnd, color);
  lcd.setLine(lftXPosStart, lftYPosStart, lftXPosEnd, lftYPosEnd, color);
  lcd.setLine(rtXPosStart, rtYPosStart, rtXPosEnd, rtYPosEnd, color);
}

void printTx(bool show) {
  int vertXPosStart = xLoc(6.25);
  int vertYPosStart = yLoc(13.5);
  int vertXPosEnd = xLoc(7.25);
  int vertYPosEnd = yLoc(13.5);

  int lftXPosStart = vertXPosStart;
  int lftYPosStart = vertYPosStart;
  int lftXPosEnd = vertXPosStart + (CHAR_HEIGHT / 2);
  int lftYPosEnd = vertYPosStart - CHAR_WIDTH;

  int rtXPosStart = vertXPosStart;
  int rtYPosStart = vertYPosStart;
  int rtXPosEnd = vertXPosStart + (CHAR_HEIGHT / 2);
  int rtYPosEnd = vertYPosStart + CHAR_WIDTH;
  
  int color = show ? SKYBLUE : BACKGROUND;

  lcd.setLine(vertXPosStart, vertYPosStart, vertXPosEnd, vertYPosEnd, color);
  lcd.setLine(lftXPosStart, lftYPosStart, lftXPosEnd, lftYPosEnd, color);
  lcd.setLine(rtXPosStart, rtYPosStart, rtXPosEnd, rtYPosEnd, color);
}
