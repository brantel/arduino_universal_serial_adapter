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
char* modeToText[4] = {
  "Phone UART",
  "DB9 - Normal",
  "DB9 - Null Mdm",
  "Cisco console"
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