#include <pebble.h>
#include "credits_window.h"

static Window *s_window;
static MenuLayer *s_menulayer_credits;

#define ROW(TITLE, SUBTITLE) { .title = (TITLE), .subtitle = (SUBTITLE) }

static SimpleMenuItem s_simplemenuitem_section1[] = {
  ROW("Alexsander Akers", "@a2"),
};
static SimpleMenuItem s_simplemenuitem_section2[] = {
  ROW("Daniel Tomlinson", "@dantoml"),
  ROW("Eric Oesterle", "@erico"),
  ROW("Henri Watson", "@henriwatson"),
  ROW("Max Bäumle", "@maxbaeumle"),
  ROW("Neal Patel", "@iNeal"),
  ROW("Patrick Balestra", "@BalestraPatrick"),
  ROW("Zach Waldowski", "@zwaldowski"),
};

static SimpleMenuSection s_simplemenusection_sections[] = {
  {
    .items = s_simplemenuitem_section1,
    .num_items = ARRAY_LENGTH(s_simplemenuitem_section1),
    .title = "Author",
  },
  {
    .items = s_simplemenuitem_section2,
    .num_items = ARRAY_LENGTH(s_simplemenuitem_section2),
    .title = "Emotional Support",
  }
};

static void initialize_ui(void);
static void handle_window_unload(Window *window);
static void menu_layer_draw_header_callback(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *callback_context);
static void menu_layer_draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context);
static int16_t menu_layer_get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context);
static int16_t menu_layer_get_header_height_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context);
static uint16_t menu_layer_get_number_of_rows_in_section_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context);
static uint16_t menu_layer_get_number_sections_callback(struct MenuLayer *menu_layer, void *callback_context);

void credits_window_push(bool animated) {
  initialize_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, animated);
}

void credits_window_pop(bool animated) {
  window_stack_remove(s_window, animated);
}

static void initialize_ui(void) {
  s_window = window_create();

  Layer *root_layer = window_get_root_layer(s_window);

  s_menulayer_credits = menu_layer_create(layer_get_bounds(root_layer));
  menu_layer_set_callbacks(s_menulayer_credits, NULL, (MenuLayerCallbacks){
    .draw_header = menu_layer_draw_header_callback,
    .draw_row = menu_layer_draw_row_callback,
    .get_cell_height = menu_layer_get_cell_height_callback,
    .get_header_height = menu_layer_get_header_height_callback,
    .get_num_rows = menu_layer_get_number_of_rows_in_section_callback,
    .get_num_sections = menu_layer_get_number_sections_callback,
  });
#if PBL_COLOR
  menu_layer_set_normal_colors(s_menulayer_credits, GColorWhite, GColorChromeYellow);
  menu_layer_set_highlight_colors(s_menulayer_credits, GColorWindsorTan, GColorWhite);
#endif
  menu_layer_set_click_config_onto_window(s_menulayer_credits, s_window);
  layer_add_child(root_layer, menu_layer_get_layer(s_menulayer_credits));
}

static void handle_window_unload(Window *window) {
  window_destroy(s_window);
  menu_layer_destroy(s_menulayer_credits);
}

static int16_t menu_layer_get_cell_height_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
#if PBL_ROUND
  return menu_layer_is_index_selected(menu_layer, cell_index)
    ? MENU_CELL_ROUND_FOCUSED_SHORT_CELL_HEIGHT
    : MENU_CELL_ROUND_UNFOCUSED_SHORT_CELL_HEIGHT;
#else
  return 44;
#endif
}

static void menu_layer_draw_header_callback(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *callback_context) {
  const char *title = s_simplemenusection_sections[section_index].title;
  GFont font = fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD);
  GTextOverflowMode overflow = GTextOverflowModeTrailingEllipsis;
  GTextAlignment align = PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft);
  GRect draw_rect = layer_get_bounds(cell_layer);
  draw_rect.origin.x += 2;
  draw_rect.size.w -= 4;
  if (section_index == 1) {
    draw_rect.origin.y += MENU_CELL_BASIC_HEADER_HEIGHT;
    draw_rect.size.h -= MENU_CELL_BASIC_HEADER_HEIGHT;
  }

#if PBL_ROUND
  const GSize size = graphics_text_layout_get_content_size(title, font, draw_rect, overflow, align);
  GPoint p0 = GPoint((draw_rect.size.w - size.w) / 2 + 1, draw_rect.origin.y + draw_rect.size.h - 2);
  GPoint p1 = GPoint(p0.x + size.w, p0.y);
  graphics_context_set_stroke_color(ctx, GColorChromeYellow);
  graphics_draw_line(ctx, p0, p1);
#endif

  graphics_context_set_text_color(ctx, PBL_IF_COLOR_ELSE(GColorWindsorTan, GColorBlack));
  graphics_draw_text(ctx, title, font, draw_rect, overflow, align, NULL);
}

static void menu_layer_draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
  SimpleMenuItem menu_item = s_simplemenusection_sections[cell_index->section].items[cell_index->row];
  menu_cell_basic_draw(ctx, cell_layer, menu_item.title, menu_item.subtitle, menu_item.icon);
}

static int16_t menu_layer_get_header_height_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
  return section_index == 0
    ? MENU_CELL_BASIC_HEADER_HEIGHT + 1
    : 2 * MENU_CELL_BASIC_HEADER_HEIGHT + 1;
}

static uint16_t menu_layer_get_number_of_rows_in_section_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
  return s_simplemenusection_sections[section_index].num_items;
}

static uint16_t menu_layer_get_number_sections_callback(struct MenuLayer *menu_layer, void *callback_context) {
  return ARRAY_LENGTH(s_simplemenusection_sections);
}
