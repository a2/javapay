#include <pebble.h>
#include "card_window.h"
#include "defines.h"

static Window *s_window;
static char s_value[] = ZEROS ZEROS ZEROS ZEROS;
static int8_t s_offset = 0;
static TextLayer *s_textlayer_prompt;
static char s_text_card_number[] = ZEROS " " ZEROS "\n" ZEROS " " ZEROS;
static TextLayer *s_textlayer_card_number;
static InverterLayer *s_inverterlayer;
static GBitmap *s_bitmap_down_arrow;
static GBitmap *s_bitmap_up_arrow;
static BitmapLayer *s_bitmaplayer_down_arrow;
static BitmapLayer *s_bitmaplayer_up_arrow;

static void handle_window_unload(Window *window);
static void initialize_ui(void);
static void click_config_provider(void *context);
static void handle_single_click(ClickRecognizerRef recognizer, void *context);
static void update_text(void);
static void update_frames(void);

void card_window_push(bool animated) {
  s_offset = 0;
  strcpy(s_value, ZEROS ZEROS ZEROS ZEROS);

  initialize_ui();

  window_set_click_config_provider(s_window, click_config_provider);
  window_set_window_handlers(s_window, (WindowHandlers){
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, animated);
}

void card_window_pop(bool animated) {
  window_stack_remove(s_window, animated);
}

char *card_window_get_value(void) {
  return s_value;
}

void card_window_set_value(char *value) {
  strncpy(s_value, value, 16);

  if (s_window != NULL) {
    update_text();
  }
}

static void initialize_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);

  Layer *root_layer = window_get_root_layer(s_window);

  s_textlayer_prompt = text_layer_create(GRect(5, 5, 134, 40));
  text_layer_set_background_color(s_textlayer_prompt, GColorBlack);
  text_layer_set_font(s_textlayer_prompt, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text(s_textlayer_prompt, "Enter your 16-digit card number:");
  text_layer_set_text_color(s_textlayer_prompt, GColorWhite);
  layer_add_child(root_layer, (Layer *)s_textlayer_prompt);

  s_textlayer_card_number = text_layer_create(GRect(5, 50, 134, 60));
  text_layer_set_background_color(s_textlayer_card_number, GColorBlack);
  text_layer_set_font(s_textlayer_card_number, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text_alignment(s_textlayer_card_number, GTextAlignmentCenter);
  text_layer_set_text_color(s_textlayer_card_number, GColorWhite);
  text_layer_set_overflow_mode(s_textlayer_card_number, GTextOverflowModeWordWrap);
  layer_add_child(root_layer, (Layer *)s_textlayer_card_number);
  update_text();

  s_inverterlayer = inverter_layer_create(GRect(21, 59, 11, 20));
  layer_add_child(root_layer, (Layer *)s_inverterlayer);

  s_bitmap_down_arrow = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DOWN_ARROW);
  s_bitmaplayer_down_arrow = bitmap_layer_create(GRect(24, 81, 5, 3));
  bitmap_layer_set_bitmap(s_bitmaplayer_down_arrow, s_bitmap_down_arrow);
  layer_add_child(root_layer, (Layer *)s_bitmaplayer_down_arrow);

  s_bitmap_up_arrow = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_UP_ARROW);
  s_bitmaplayer_up_arrow = bitmap_layer_create(GRect(24, 54, 5, 3));
  bitmap_layer_set_bitmap(s_bitmaplayer_up_arrow, s_bitmap_up_arrow);
  layer_add_child(root_layer, (Layer *)s_bitmaplayer_up_arrow);
}

static void handle_window_unload(Window *window) {
  window_destroy(window);
  text_layer_destroy(s_textlayer_prompt);
  text_layer_destroy(s_textlayer_card_number);
  inverter_layer_destroy(s_inverterlayer);
  gbitmap_destroy(s_bitmap_down_arrow);
  gbitmap_destroy(s_bitmap_up_arrow);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_BACK, handle_single_click);
  window_single_click_subscribe(BUTTON_ID_SELECT, handle_single_click);
  window_single_repeating_click_subscribe(BUTTON_ID_UP, 250, handle_single_click);
  window_single_repeating_click_subscribe(BUTTON_ID_DOWN, 250, handle_single_click);
}

static void handle_single_click(ClickRecognizerRef recognizer, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "card_window -> handle_single_click");
  switch (click_recognizer_get_button_id(recognizer)) {
    case BUTTON_ID_BACK:
      if (s_offset > 0) {
        s_offset--;
        update_frames();
      } else {
        card_window_pop(true);
      }
      break;
    case BUTTON_ID_UP:
      if (s_value[s_offset] == '9') {
        s_value[s_offset] = '0';
      } else {
        s_value[s_offset]++;
      }
      update_text();
      break;
    case BUTTON_ID_SELECT:
      if (s_offset < 15) {
        s_offset++;
        update_frames();
      } else {
        persist_write_string(STORAGE_CARD_NUMBER, s_value);
        card_window_pop(true);
      }
      break;
    case BUTTON_ID_DOWN:
      if (s_value[s_offset] == '0') {
        s_value[s_offset] = '9';
      } else {
        s_value[s_offset]--;
      }
      update_text();
      break;
    default:
      break;
  }
}

static void update_text(void) {
  for (size_t i = 0; i < 4; i++) {
    memcpy(s_text_card_number + 5 * i, s_value + 4 * i, 4);
  }

  text_layer_set_text(s_textlayer_card_number, s_text_card_number);
}

static void update_frames(void) {
  GRect inverter_frame = GRect(21 + (s_offset % 8) * 12 + (s_offset % 8 < 4 ? 0 : 5), 54 + 5, 11, 20);
  GRect up_arrow_frame = GRect(inverter_frame.origin.x + 3, inverter_frame.origin.y - 5, 5, 3);
  GRect down_arrow_frame = GRect(inverter_frame.origin.x + 3, inverter_frame.origin.y + inverter_frame.size.h + 2, 5, 3);
  if (s_offset >= 8) {
    inverter_frame.origin.y += 28;
    up_arrow_frame.origin.y += 28;
    down_arrow_frame.origin.y += 28;
  }
  layer_set_frame((Layer *)s_inverterlayer, inverter_frame);
  layer_set_frame((Layer *)s_bitmaplayer_down_arrow, down_arrow_frame);
  layer_set_frame((Layer *)s_bitmaplayer_up_arrow, up_arrow_frame);
}
