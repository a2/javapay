#include <pebble.h>
#include "card_window.h"
#include "defines.h"
#include "pdf417.h"
#include "settings_window.h"

static Window *s_window;
static char s_value[] = ZEROS ZEROS ZEROS ZEROS;
static GBitmap *s_bitmap_app_icon;
static BitmapLayer *s_bitmaplayer_app_icon;
static GBitmap *s_bitmap_barcode;
static BitmapLayer *s_bitmaplayer_barcode;
static char s_text_card_number[20] = ZEROS " " ZEROS " " ZEROS " " ZEROS;
static TextLayer *s_textlayer_card_number;
static bool s_has_appeared = false;

static void handle_window_appear(Window *window);
static void handle_window_unload(Window *window);
static void initialize_ui(void);
static void click_config_provider(void *context);
static void handle_single_click(ClickRecognizerRef recognizer, void *context);

void barcode_window_push(bool animated) {
  initialize_ui();
  s_has_appeared = false;

  window_set_click_config_provider(s_window, click_config_provider);
  window_set_window_handlers(s_window, (WindowHandlers){
    .appear = handle_window_appear,
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, animated);
}

void barcode_window_pop(bool animated) {
  window_stack_remove(s_window, animated);
}

static void initialize_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, PBL_IF_COLOR_ELSE(GColorWindsorTan, GColorBlack));
#if PBL_SDK_2
  window_set_fullscreen(s_window, true);
#endif

  const GRect barcode_frame = PBL_IF_ROUND_ELSE((GRect(0, 63, 180, 54)), (GRect(0, 57, 144, 54)));
  s_bitmaplayer_barcode = bitmap_layer_create(barcode_frame);
  bitmap_layer_set_alignment(s_bitmaplayer_barcode, GAlignCenter);
  bitmap_layer_set_background_color(s_bitmaplayer_barcode, GColorWhite);

  const GRect app_icon_frame = PBL_IF_ROUND_ELSE((GRect(30, 33, 119, 25)), (GRect(12, 25, 119, 25)));
  s_bitmap_app_icon = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_JAVAPAY);
  s_bitmaplayer_app_icon = bitmap_layer_create(app_icon_frame);
  bitmap_layer_set_bitmap(s_bitmaplayer_app_icon, s_bitmap_app_icon);
  bitmap_layer_set_compositing_mode(s_bitmaplayer_app_icon, PBL_IF_COLOR_ELSE(GCompOpSet, GCompOpAssign));

  const GRect card_number_frame = PBL_IF_ROUND_ELSE((GRect(19, 121, 142, 20)), (GRect(1, 113, 142, 20)));
  s_textlayer_card_number = text_layer_create(card_number_frame);
  text_layer_set_background_color(s_textlayer_card_number, PBL_IF_COLOR_ELSE(GColorWindsorTan, GColorBlack));
  text_layer_set_font(s_textlayer_card_number, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
  text_layer_set_text_alignment(s_textlayer_card_number, GTextAlignmentCenter);
  text_layer_set_text_color(s_textlayer_card_number, GColorWhite);

  Layer *root_layer = window_get_root_layer(s_window);
  layer_add_child(root_layer, (Layer *)s_bitmaplayer_barcode);
  layer_add_child(root_layer, (Layer *)s_bitmaplayer_app_icon);
  layer_add_child(root_layer, (Layer *)s_textlayer_card_number);
}

static void persist_read_barcode(void) {
  if (E_DOES_NOT_EXIST == persist_read_string(STORAGE_CARD_NUMBER, s_value, sizeof(s_value))) {
    return;
  }

  s_bitmap_barcode = pdf417_create_bitmap(s_value);
  bitmap_layer_set_bitmap(s_bitmaplayer_barcode, s_bitmap_barcode);

  for (int i = 0; i < 4; i++) {
    memcpy(s_text_card_number + 5 * i, s_value + 4 * i, 4);
  }
  text_layer_set_text(s_textlayer_card_number, s_text_card_number);
}

static void app_timer_callback(void *data) {
  card_window_push(true);
}

static void handle_window_appear(Window *window) {
  if (!persist_exists(STORAGE_CARD_NUMBER)) {
    if (s_has_appeared) {
      window_stack_pop_all(true);
    } else {
      app_timer_register(200, app_timer_callback, NULL);
    }
  }

  if (s_bitmap_barcode != NULL) {
    gbitmap_destroy(s_bitmap_barcode), s_bitmap_barcode = NULL;
  }

  persist_read_barcode();
  s_has_appeared = true;
}

static void handle_window_unload(Window *window) {
  window_destroy(window);
  gbitmap_destroy(s_bitmap_app_icon);
  bitmap_layer_destroy(s_bitmaplayer_app_icon);
  bitmap_layer_destroy(s_bitmaplayer_barcode);
  text_layer_destroy(s_textlayer_card_number);

  if (s_bitmap_barcode != NULL) {
    gbitmap_destroy(s_bitmap_barcode), s_bitmap_barcode = NULL;
  }
}

static void click_config_provider(void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "barcode_window -> click_config_provider");
  window_single_click_subscribe(BUTTON_ID_SELECT, handle_single_click);
}

static void handle_single_click(ClickRecognizerRef recognizer, void *context) {
  settings_window_push(true);
}
