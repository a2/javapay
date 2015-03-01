#pragma once
#include <pebble.h>
  
// input must match /[0-9]{16}/
extern GBitmap *pdf417_create_bitmap(const char *input);