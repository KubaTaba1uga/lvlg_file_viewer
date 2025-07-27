#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "lvgl.h"

uint32_t my_get_millis(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint32_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

int main(void) {
  /* your_dr2iver_init(); */

  lv_init();

  lv_tick_set_cb(my_get_millis);

  /* Create X11 driver */
  lv_display_t *disp = lv_x11_window_create("LVGL X11 Simulation", 200, 600);
  lv_x11_inputs_create(disp, NULL);

  /* Create widgets */
  lv_obj_t *label = lv_label_create(lv_screen_active());
  lv_label_set_text(label, "Hello LVGL!");

  /* Make LVGL periodically execute its tasks */
  while (1) {
    lv_timer_handler();
    usleep(5); /*Wait 5 milliseconds before processing LVGL timer again*/
  }

  return 0;
}
