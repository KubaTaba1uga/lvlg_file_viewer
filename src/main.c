#include <lvgl.h>
#include <stc/cstr.h>
#include <stdint.h>
#include <stdio.h>
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

int main(void) {
  lv_init();

  lv_tick_set_cb(my_get_millis);

  init_x11_driver();

  // TO-DO read path from args
  cstr title = cstr_from("My Super Secret File");

  lv_obj_t *main_col = lv_obj_create(lv_screen_active());
  lv_obj_set_size(main_col, SCREEN_WIDTH, SCREEN_HEIGHT);
  lv_obj_set_flex_flow(main_col, LV_FLEX_FLOW_COLUMN);

  show_tiltle_bar(title, main_col);
  show_reading_area(main_col);

  /* Make LVGL periodically execute its tasks */
  while (1) {
    /* lv_task_handler(); */
    usleep(lv_timer_handler());
  }

  return 0;
}
