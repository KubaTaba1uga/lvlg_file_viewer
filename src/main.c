#include <lvgl.h>
#include <stc/cstr.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "reading_area/reading_area.h"
#include "title_bar/title_bar.h"
#include "utils/settings.h"
#include "x11_driver/x11_driver.h"

uint32_t my_get_millis(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint32_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

void my_btn_event_cb(lv_event_t *e) { printf("Clicked\n"); }

int main(int argc, char *argv[]) {
  if (argc != 2) {
    puts("Usage: lvgl_file_viewer <file path>");
    exit(EXIT_FAILURE);
  }

  lv_init();

  lv_tick_set_cb(my_get_millis);

  init_x11_driver();

  cstr title = cstr_from(argv[1]);

  lv_obj_t *main_col = lv_obj_create(lv_screen_active());
  lv_obj_set_size(main_col, lv_pct(100), lv_pct(100));
  lv_obj_set_flex_flow(main_col, LV_FLEX_FLOW_COLUMN);

  show_tiltle_bar(title, main_col);

  // TO-DO read file from path
  show_reading_area(main_col);

  uint32_t idle_time;
  while (true) {
    idle_time = lv_timer_handler();
    usleep(idle_time * 1000);
  }

  cstr_drop(&title);

  return 0;
}
