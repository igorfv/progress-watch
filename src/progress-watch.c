#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID {0x5C, 0x47, 0x37, 0xAD, 0x4F, 0x68, 0x45, 0x8D, 0xA4, 0x30, 0x7E, 0x10, 0xEE, 0x07, 0x10, 0x80}
PBL_APP_INFO(MY_UUID,
             "Progress Watch", "Igor Vieira",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;

Layer main_layer;


void text_n_bars_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  graphics_context_set_stroke_color(ctx, GColorWhite);

  //Bars
    //Year
    graphics_draw_line(ctx, GPoint(5, 24),      GPoint(144-7, 24));
    graphics_draw_line(ctx, GPoint(5, 24+6),    GPoint(144-7, 24+6));
    graphics_draw_line(ctx, GPoint(4, 25),      GPoint(4, 25+4));
    graphics_draw_line(ctx, GPoint(144-6, 25),  GPoint(144-6, 25+4));

    //Month
    graphics_draw_line(ctx, GPoint(5, 55),      GPoint(144-7, 55));
    graphics_draw_line(ctx, GPoint(5, 55+6),    GPoint(144-7, 55+6));
    graphics_draw_line(ctx, GPoint(4, 56),      GPoint(4, 56+4));
    graphics_draw_line(ctx, GPoint(144-6, 56),  GPoint(144-6, 56+4));

    //Week
    graphics_draw_line(ctx, GPoint(5, 86),      GPoint(144-7, 86));
    graphics_draw_line(ctx, GPoint(5, 86+6),    GPoint(144-7, 86+6));
    graphics_draw_line(ctx, GPoint(4, 87),      GPoint(4, 87+4));
    graphics_draw_line(ctx, GPoint(144-6, 87),  GPoint(144-6, 87+4));

    //Day
    graphics_draw_line(ctx, GPoint(5, 117),     GPoint(144-7, 117));
    graphics_draw_line(ctx, GPoint(5, 117+6),   GPoint(144-7, 117+6));
    graphics_draw_line(ctx, GPoint(4, 118),     GPoint(4, 118+4));
    graphics_draw_line(ctx, GPoint(144-6, 118), GPoint(144-6, 118+4));

}


void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, GColorBlack);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
  };
  app_event_loop(params, &handlers);
}
