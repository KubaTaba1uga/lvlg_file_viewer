#include <lvgl.h>
#include <stc/cstr.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "reading_area/reading_area.h"
#include "stc/cstr.h"
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

  lv_obj_t *main_col = lv_obj_create(lv_screen_active());
  lv_obj_set_size(main_col, lv_pct(100), lv_pct(100));
  lv_obj_set_flex_flow(main_col, LV_FLEX_FLOW_COLUMN);

  cstr file_path = cstr_from(argv[1]);
  show_tiltle_bar(file_path, main_col);

  FILE *fp = fopen(cstr_str(&file_path), "rb");
  if (!fp) {
    perror("Cannot open file");
    exit(EXIT_FAILURE);
  }

  cstr file_buf = cstr_with_capacity(16 * 1024);
  csview file_view = cstr_sv(&file_buf);

  file_view.size =
      fread((void *)file_view.buf, sizeof(char), cstr_capacity(&file_buf), fp);

  show_reading_area(file_view, main_col);
  fclose(fp);

  uint32_t idle_time;
  while (true) {
    idle_time = lv_timer_handler();
    usleep(idle_time * 10000);
  }

  lv_obj_del(main_col);
  cstr_drop(&file_path);
  cstr_drop(&file_buf);

  return 0;
}
