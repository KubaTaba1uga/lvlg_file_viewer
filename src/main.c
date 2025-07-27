#include <lvgl.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "title_bar/title_bar.h"
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

  /*Create a white label, set its text and align it to the center*/
  /* lv_obj_t *label = lv_label_create(lv_screen_active()); */
  /* lv_label_set_text(label, "Title"); */
  /* lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), */
  /*                             LV_PART_MAIN); */

  lv_example_flex_1();

  /* Make LVGL periodically execute its tasks */
  while (1) {
    /* lv_task_handler(); */
    usleep(lv_timer_handler());
  }

  return 0;
}
