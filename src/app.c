#include <pebble.h>
#include "barcode_window.h"

int main(void) {
  barcode_window_push(true);
  app_event_loop();
}
