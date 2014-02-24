#include <pebble.h>



Window* window;

TextLayer *year_layer;
TextLayer *month_layer;
TextLayer *week_layer;
TextLayer *day_layer;
static struct tm *tn;
TextLayer *text_time_layer;

Layer *bars_layer;
Layer *main_layer;
Layer *window_layer;

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
time_t now = time(NULL);
	tn = localtime(&now);
  graphics_context_set_stroke_color(ctx, GColorWhite);
  //Progress bars

  //% of date
  //Year
  float year;
  int year_percent;
  
  year = tn->tm_yday;
  year = ((double)100/366)*year; //Percent of year

  //Month
  float month;
  int month_percent;
  int isLeapYear = (tn->tm_year%4 == 0)?1:0;
  int daysInMonth = (tn->tm_mon + 1 == 2) ? (28 + isLeapYear) : 31 - ((tn->tm_mon) % 7 % 2);
  
  month = tn->tm_mday;
  month = ((double)100/daysInMonth)*month; //Percent of month

  //Week
  float week;
  //int the_hour; 
  int week_percent;
  
  week = tn->tm_wday;
  week = week*24 + tn->tm_hour;
  week = ((double)100/(7*24))*week; //Percent of Week

  //Day
  float day;
  int day_percent;
  
  day = tn->tm_hour;
  day = day*60 + tn->tm_min;
  day = ((double)100/(24*60))*day; //Percent of year


  //% of progress bar
  //Year
  year = ((double)134/100)*year; //Percent of bar based on % of year
  year_percent = (int)year;

  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, GRect(5, 25, year_percent, 5), 0, GCornerNone);

  //Month
  month = ((double)134/100)*month; //Percent of bar based on % of month
  month_percent = (int)month;

  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, GRect(5, 56, month_percent, 5), 0, GCornerNone);

  //Week
  week = ((double)134/100)*week; //Percent of bar based on % of year
  week_percent = (int)week;

  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, GRect(5, 87, week_percent, 5), 0, GCornerNone);

  //Day
  day = ((double)134/100)*day; //Percent of bar based on % of year
  day_percent = (int)day;

  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, GRect(5, 118, day_percent, 5), 0, GCornerNone);
}

void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {

  static char time_text[] = "00:00";
  char *time_format;

  //Time
  if (clock_is_24h_style()) {
    time_format = "%R";
  } else {
    time_format = "%I:%M";
  }

 
  strftime(time_text, sizeof(time_text), time_format, tick_time);

  if (!clock_is_24h_style() && (time_text[0] == '0')) {
    memmove(time_text, &time_text[1], sizeof(time_text) - 1);
  }

  text_layer_set_text(text_time_layer, time_text);

  //Redraw layer
  layer_mark_dirty(main_layer);
}


static void handle_init(void) {

  window = window_create();
  window_stack_push(window, true /* Animated */);
  window_set_background_color(window, GColorBlack);

	  window_layer = window_get_root_layer(window);
  //Texts
    //Year
    year_layer = text_layer_create(GRect(8, 7, 144-16, 7+12));
    text_layer_set_text_color(year_layer, GColorWhite);
    text_layer_set_background_color(year_layer, GColorClear);
    text_layer_set_font(year_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
    text_layer_set_text(year_layer, "Year");
    layer_add_child(window_layer, text_layer_get_layer(year_layer));

    //Month
    month_layer = text_layer_create(GRect(8, 38, 144-16, 38+12));
    text_layer_set_text_color(month_layer, GColorWhite);
    text_layer_set_background_color(month_layer, GColorClear);
    text_layer_set_font(month_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
    text_layer_set_text(month_layer, "Month");
    layer_add_child(window_layer, text_layer_get_layer(month_layer));

    //Week
    week_layer = text_layer_create(GRect(8, 69, 144-16, 69+12));
    text_layer_set_text_color(week_layer, GColorWhite);
    text_layer_set_background_color(week_layer, GColorClear);
    text_layer_set_font(week_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
    text_layer_set_text(week_layer, "Week");
    layer_add_child(window_layer, text_layer_get_layer(week_layer));

    //Day
    day_layer = text_layer_create(GRect(8, 100, 144-16, 100+12));
    text_layer_set_text_color(day_layer, GColorWhite);
    text_layer_set_background_color(day_layer, GColorClear);
    text_layer_set_font(day_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
    text_layer_set_text(day_layer, "Day");
    layer_add_child(window_layer, text_layer_get_layer(day_layer));

  //Clock text
  text_time_layer = text_layer_create(GRect(0, 127, 144, 127+26));
  text_layer_set_text_color(text_time_layer, GColorWhite);
  text_layer_set_background_color(text_time_layer, GColorClear);
  text_layer_set_font(text_time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(text_time_layer, GTextAlignmentCenter);
  text_layer_set_text(text_time_layer, "00:00");
  layer_add_child(window_layer, text_layer_get_layer(text_time_layer));


  bars_layer = layer_create(layer_get_frame(window_layer));
  layer_set_update_proc(bars_layer, bars_update_callback);
  layer_add_child(window_layer, bars_layer);

  main_layer = layer_create(layer_get_frame(window_layer));
  layer_set_update_proc(main_layer, progress_update_callback);
  layer_add_child(window_layer, main_layer);
	
  tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);
}


static void handle_destroy(void) {
  //Texts
    //Year
    text_layer_destroy(year_layer);

    //Month
    text_layer_destroy(month_layer);

    //Week
    text_layer_destroy(week_layer);

    //Day
    text_layer_destroy(day_layer);

  //Clock text
  text_layer_destroy(text_time_layer);
  
  layer_destroy(bars_layer);
  
  layer_destroy(main_layer);
  tick_timer_service_unsubscribe();
  layer_destroy(window_layer);
	
  window_destroy(window);
}


int main(void) {
   handle_init();

   app_event_loop();
	
   handle_destroy();
}
