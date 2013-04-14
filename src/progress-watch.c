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


void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
  };
  app_event_loop(params, &handlers);
}
