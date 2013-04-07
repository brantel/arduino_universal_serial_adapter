/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
  by: Mike Crosson
  Nusku Networks
  date: 2013/03/09
  license: CC-BY SA 3.0 - Creative commons share-alike 3.0
  use this code however you'd like, just keep this license and
  attribute.
*/

#include "Project.h"

// Map a mode -> text value
char* modeToText[3] = {
  "Serial TTL",
  "DB9 - Null Mdm",
  "Cisco console"
};

char* voltageToText[3] = {
  "1.8V",
  "3.3V",
  "5.0V"
};

// Known and supported line speeds
linespeedinfo linespeeds[6] = {
  { "2400b", 2400 },
  { "9600b", 9600 },
  { "19.2k", 19200 },
  { "38.4k", 38400 },
  { "57.5k", 57600 },
  { "115k", 115200 }
};

char* timeoutToText[5] = {
  "10s",
  "30s",
  "1m",
  "5m",
  "Never"
};
