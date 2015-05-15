#include <pebble.h>
#include "credits_window.h"

static Window *s_window;
static SimpleMenuLayer *s_simplemenulayer_credits;

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
static void destroy_ui(void);
static void handle_window_unload(Window *window);

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

  s_simplemenulayer_credits = simple_menu_layer_create(layer_get_bounds(root_layer), s_window, s_simplemenusection_sections, ARRAY_LENGTH(s_simplemenusection_sections), NULL);
#if PBL_PLATFORM_BASALT
  MenuLayer *menu_layer = simple_menu_layer_get_menu_layer(s_simplemenulayer_credits);
  menu_layer_set_normal_colors(menu_layer, GColorWhite, GColorWindsorTan);
  menu_layer_set_highlight_colors(menu_layer, GColorWindsorTan, GColorWhite);
#endif

  layer_add_child(root_layer, simple_menu_layer_get_layer(s_simplemenulayer_credits));
}

static void destroy_ui(void) {
  window_destroy(s_window);
  simple_menu_layer_destroy(s_simplemenulayer_credits);
}

static void handle_window_unload(Window *window) {
  destroy_ui();
}
