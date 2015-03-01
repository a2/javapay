#include <pebble.h>
#include "card_window.h"
#include "credits_window.h"
#include "defines.h"
#include "settings_window.h"

static Window *s_window;
static MenuLayer *s_menulayer;
static const char *const message = "JavaPay is free. Heart it on the Pebble App Store if it helped you, and please tell your friends. pbl.io/javapay";

static void handle_window_unload(Window *window);
static void initialize_ui(void);
static void menu_layer_draw_header_callback(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *callback_context);
static void menu_layer_draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context);
static int16_t menu_layer_get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context);
static int16_t menu_layer_get_header_height_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context);
static uint16_t menu_layer_get_number_of_rows_in_section_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context);
static uint16_t menu_layer_get_number_sections_callback(struct MenuLayer *menu_layer, void *callback_context);
static void menu_layer_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context);

void settings_window_push(bool animated) {
  initialize_ui();

  window_set_window_handlers(s_window, (WindowHandlers){
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, animated);
}

void settings_window_pop(bool animated) {
  window_stack_remove(s_window, animated);
}

static void initialize_ui(void) {
  s_window = window_create();

  Layer *root_layer = window_get_root_layer(s_window);

  s_menulayer = menu_layer_create(layer_get_bounds(root_layer));
  menu_layer_set_callbacks(s_menulayer, NULL, (MenuLayerCallbacks){
    .draw_header = menu_layer_draw_header_callback,
    .draw_row = menu_layer_draw_row_callback,
    .get_cell_height = menu_layer_get_cell_height_callback,
    .get_header_height = menu_layer_get_header_height_callback,
    .get_num_rows = menu_layer_get_number_of_rows_in_section_callback,
    .get_num_sections = menu_layer_get_number_sections_callback,
    .select_click = menu_layer_select_callback,
  });
  menu_layer_set_click_config_onto_window(s_menulayer, s_window);
  layer_add_child(root_layer, menu_layer_get_layer(s_menulayer));
}

static void handle_window_unload(Window *window) {
  window_destroy(window);
  menu_layer_destroy(s_menulayer);
}

static int16_t menu_layer_get_cell_height_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
  switch (cell_index->section) {
    case 0: {
      static int16_t h = -1;
      if (h < 0) {
        GRect draw_rect = layer_get_bounds(menu_layer_get_layer(menu_layer));
        draw_rect.origin.x += 4;
        draw_rect.size.w -= 8;
        GSize size = graphics_text_layout_get_content_size(message, fonts_get_system_font(FONT_KEY_GOTHIC_18), draw_rect, GTextOverflowModeWordWrap, GTextAlignmentLeft);
        h = size.h + 8;
      }
      return h;
    }
    case 1:
      return 32;
    default:
      return 44;
  }
}

static void menu_layer_draw_header_callback(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *callback_context) {
  if (section_index == 2) {
    graphics_context_set_stroke_color(ctx, GColorBlack);
    graphics_context_set_text_color(ctx, GColorBlack);

    GRect draw_rect = layer_get_bounds(cell_layer);
    graphics_draw_line(ctx, GPoint(0, 1), GPoint(draw_rect.size.w, 1));

    draw_rect.origin.y++;

    static GTextLayoutCacheRef cache;
    graphics_draw_text(ctx, "Version 1.1", fonts_get_system_font(FONT_KEY_GOTHIC_14), draw_rect, GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, cache);
  }
}

static void menu_layer_draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
  switch (cell_index->section) {
    case 0: {
      graphics_context_set_text_color(ctx, GColorBlack);

      GRect draw_rect = layer_get_bounds(cell_layer);
      draw_rect.origin.x += 4;
      draw_rect.size.w -= 8;

      static GTextLayoutCacheRef cache;
      graphics_draw_text(ctx, message, fonts_get_system_font(FONT_KEY_GOTHIC_18), draw_rect, GTextOverflowModeWordWrap, GTextAlignmentLeft, cache);
      break;
    }
    case 1: {
      const char *text = "";
      switch (cell_index->row) {
        case 0:
          text = "Change Card";
          break;
        case 1:
          text = "Credits";
          break;
      }
      menu_cell_title_draw(ctx, cell_layer, text);
      break;
    }
  }
}

static int16_t menu_layer_get_header_height_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
  switch (section_index) {
    case 0:
      return 0;
    case 1:
      return 1;
    case 2:
      return 18;
    default:
      return 16;
  }
}

static uint16_t menu_layer_get_number_of_rows_in_section_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
  switch (section_index) {
    case 0:
      return 1;
    case 1:
      return 2;
    case 2:
      return 0;
    default:
      return 0;
  }
}

static uint16_t menu_layer_get_number_sections_callback(struct MenuLayer *menu_layer, void *callback_context) {
  return 3;
}

static void menu_layer_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
  if (cell_index->section == 1) {
    if (cell_index->row == 0) {
      card_window_push(true);
    } else {
      credits_window_push(true);
    }
  }
}
