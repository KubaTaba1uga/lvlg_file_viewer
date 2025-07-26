#define _POSIX_C_SOURCE 199309L

#include "lvgl.h"
#include <stdint.h>
#include <time.h>

uint32_t my_get_millis(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint32_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

int main(void) {
  /* your_dr2iver_init(); */

  lv_init();

  lv_tick_set_cb(my_get_millis);

  lv_display_t *display = lv_display_create(320, 240);

  /* /\*LVGL will render to this 1/10 screen sized buffer for 2 bytes/pixel*\/
   */
  static uint8_t buf[320 * 240 / 10 * 2];
  lv_display_set_buffers(display, buf, NULL, LV_DISPLAY_RENDER_MODE_PARTIAL);

  /* /\*This callback will display the rendered image*\/ */

  /* /\*Create widgets*\/ */
  /* lv_obj_t *label = lv_label_create(lv_screen_active()); */
  /* lv_label_set_text(label, "Hello LVGL!"); */

  /* /\*Make LVGL periodically execute its tasks*\/ */
  /* while (1) { */
  /*   lv_timer_handler(); */
  /*   my_sleep(5); /\*Wait 5 milliseconds before processing LVGL timer again*\/
   */
  /* } */

  return 0;
}

/* /\*Return the elapsed milliseconds since startup. */
/*  *It needs to be implemented by the user*\/ */
/* uint32_t my_get_millis(void) { return my_tick_ms; } */

/* /\*Copy the rendered image to the screen. */
/*  *It needs to be implemented by the user*\/ */
/* void my_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_buf)
 * { */
/*   /\*Show the rendered image on the display*\/ */
/*   my_display_update(area, px_buf); */

/*   /\*Indicate that the buffer is available. */
/*    *If DMA were used, call in the DMA complete interrupt*\/ */
/*   lv_display_flush_ready(); */
/* } */
