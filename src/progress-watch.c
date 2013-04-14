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

TextLayer year_layer;
TextLayer month_layer;
TextLayer week_layer;
TextLayer day_layer;

TextLayer text_time_layer;

Layer bars_layer;
Layer main_layer;


void bars_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  graphics_context_set_stroke_color(ctx, GColorWhite);

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

void progress_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  graphics_context_set_stroke_color(ctx, GColorWhite);
  //Progress bars
  PblTm t;
  get_time(&t);

  //% of date
  //Year
  float year;
  int year_percent;
  
  year = t.tm_yday;
  year = ((double)100/366)*year; //Percent of year


  //Month
  float month;
  int month_percent;
  int isLeapYear = (t.tm_year%4 == 0)?1:0;
  int daysInMonth = (t.tm_mon + 1 == 2) ? (28 + isLeapYear) : 31 - ((t.tm_mon) % 7 % 2);
  
  month = t.tm_mday;
  month = ((double)100/daysInMonth)*month; //Percent of month

  //Week
  float week;
  int week_percent;
  
  week = t.tm_wday;
  week = ((double)100/6)*week; //Percent of Week

  //Day
  float day;
  int day_percent;
  
  day = t.tm_hour;
  day = ((double)100/23)*day; //Percent of year


  //% of progress bar
  //Year
  year = ((double)134/100)*year; //Percent of bar based on % of year
  year_percent = (int)year;

  graphics_context_set_fill_color(app_get_current_graphics_context(), GColorWhite);
  graphics_fill_rect(app_get_current_graphics_context(), GRect(5, 25, year_percent, 5), 0, GCornerNone);

  //Month
  month = ((double)134/100)*month; //Percent of bar based on % of month
  month_percent = (int)month;

  graphics_context_set_fill_color(app_get_current_graphics_context(), GColorWhite);
  graphics_fill_rect(app_get_current_graphics_context(), GRect(5, 56, month_percent, 5), 0, GCornerNone);

  //Week
  week = ((double)134/100)*week; //Percent of bar based on % of year
  week_percent = (int)week;

  graphics_context_set_fill_color(app_get_current_graphics_context(), GColorWhite);
  graphics_fill_rect(app_get_current_graphics_context(), GRect(5, 87, week_percent, 5), 0, GCornerNone);

  //Day
  day = ((double)134/100)*day; //Percent of bar based on % of year
  day_percent = (int)day;

  graphics_context_set_fill_color(app_get_current_graphics_context(), GColorWhite);
  graphics_fill_rect(app_get_current_graphics_context(), GRect(5, 118, day_percent, 5), 0, GCornerNone);
}


void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, GColorBlack);

  //Texts
    //Year
    text_layer_init(&year_layer, GRect(8, 7, 144-16, 7+12));
    text_layer_set_text_color(&year_layer, GColorWhite);
    text_layer_set_background_color(&year_layer, GColorClear);
    text_layer_set_font(&year_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
    text_layer_set_text(&year_layer, "Year");
    layer_add_child(&window.layer, &year_layer.layer);

    //Month
    text_layer_init(&month_layer, GRect(8, 38, 144-16, 38+12));
    text_layer_set_text_color(&month_layer, GColorWhite);
    text_layer_set_background_color(&month_layer, GColorClear);
    text_layer_set_font(&month_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
    text_layer_set_text(&month_layer, "Month");
    layer_add_child(&window.layer, &month_layer.layer);

    //Week
    text_layer_init(&week_layer, GRect(8, 69, 144-16, 69+12));
    text_layer_set_text_color(&week_layer, GColorWhite);
    text_layer_set_background_color(&week_layer, GColorClear);
    text_layer_set_font(&week_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
    text_layer_set_text(&week_layer, "Week");
    layer_add_child(&window.layer, &week_layer.layer);

    //Day
    text_layer_init(&day_layer, GRect(8, 100, 144-16, 100+12));
    text_layer_set_text_color(&day_layer, GColorWhite);
    text_layer_set_background_color(&day_layer, GColorClear);
    text_layer_set_font(&day_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
    text_layer_set_text(&day_layer, "Day");
    layer_add_child(&window.layer, &day_layer.layer);

  //Clock text
  text_layer_init(&text_time_layer, GRect(0, 127, 144, 127+26));
  text_layer_set_text_color(&text_time_layer, GColorWhite);
  text_layer_set_background_color(&text_time_layer, GColorClear);
  text_layer_set_font(&text_time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(&text_time_layer, GTextAlignmentCenter);
  text_layer_set_text(&text_time_layer, "00:00");
  layer_add_child(&window.layer, &text_time_layer.layer);


  layer_init(&bars_layer, window.layer.frame);
  bars_layer.update_proc = &bars_update_callback;
  layer_add_child(&window.layer, &bars_layer);

  layer_init(&main_layer, window.layer.frame);
  main_layer.update_proc = &progress_update_callback;
  layer_add_child(&window.layer, &main_layer);
}


void handle_minute_tick(AppContextRef ctx, PebbleTickEvent *t) {
  (void)ctx;

  static char time_text[] = "00:00";
  char *time_format;

  //Time
  if (clock_is_24h_style()) {
    time_format = "%R";
  } else {
    time_format = "%I:%M";
  }

  string_format_time(time_text, sizeof(time_text), time_format, t->tick_time);

  if (!clock_is_24h_style() && (time_text[0] == '0')) {
    memmove(time_text, &time_text[1], sizeof(time_text) - 1);
  }

  text_layer_set_text(&text_time_layer, time_text);

  //Redraw layer
  layer_mark_dirty(&main_layer);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,

    .tick_info = {
      .tick_handler = &handle_minute_tick,
      .tick_units = MINUTE_UNIT
    }

  };
  app_event_loop(params, &handlers);
}
