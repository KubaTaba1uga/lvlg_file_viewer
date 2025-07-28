#ifndef LVGL_FILE_VIEWER_READING_AREA_H
#define LVGL_FILE_VIEWER_READING_AREA_H

#include "c_minilib_error.h"
#include "lvgl.h"
#include "stc/cstr.h"
#include "utils/settings.h"
#include <src/core/lv_obj_pos.h>
#include <src/misc/lv_area.h>
#include <src/widgets/label/lv_label.h>

void show_reading_area(csview buffer, lv_obj_t *main_obj) {
  lv_obj_t *reading_area = lv_obj_create(main_obj);

  lv_obj_set_size(reading_area, lv_pct(100), lv_pct(85));
  lv_obj_align(reading_area, LV_ALIGN_TOP_LEFT, 0, 5);

  lv_obj_t *text = lv_label_create(reading_area);
  lv_obj_set_width(text, lv_pct(100));
  lv_label_set_text_fmt(text, "%.*s", (int)buffer.size, buffer.buf);
};

#endif // LVGL_FILE_VIEWER_READING_AREA_H
