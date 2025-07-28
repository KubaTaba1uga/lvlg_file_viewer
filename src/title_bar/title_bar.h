#ifndef LVGL_FILE_VIEWER_TITLE_BAR_H
#define LVGL_FILE_VIEWER_TITLE_BAR_H

#include "c_minilib_error.h"
#include "lvgl.h"
#include "stc/cstr.h"
#include "utils/settings.h"
#include <src/misc/lv_area.h>

void lv_example_flex_1(void) {
  /*Create a container with ROW flex direction*/
  lv_obj_t *cont_row = lv_obj_create(lv_screen_active());
  lv_obj_set_size(cont_row, 300, 75);
  lv_obj_align(cont_row, LV_ALIGN_TOP_MID, 0, 5);
  lv_obj_set_flex_flow(cont_row, LV_FLEX_FLOW_ROW);

  /*Create a container with COLUMN flex direction*/
  lv_obj_t *cont_col = lv_obj_create(lv_screen_active());
  lv_obj_set_size(cont_col, 200, 150);
  lv_obj_align_to(cont_col, cont_row, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
  lv_obj_set_flex_flow(cont_col, LV_FLEX_FLOW_COLUMN);

  uint32_t i;
  for (i = 0; i < 10; i++) {
    lv_obj_t *obj;
    lv_obj_t *label;

    /*Add items to the row*/
    obj = lv_button_create(cont_row);
    lv_obj_set_size(obj, 100, LV_PCT(100));

    label = lv_label_create(obj);
    lv_label_set_text_fmt(label, "Item: %" LV_PRIu32 "", i);
    lv_obj_center(label);

    /*Add items to the column*/
    obj = lv_button_create(cont_col);
    lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);

    label = lv_label_create(obj);
    lv_label_set_text_fmt(label, "Item: %" LV_PRIu32, i);
    lv_obj_center(label);
  }
}

void show_tiltle_bar(cstr title, lv_obj_t *main_obj) {
  lv_obj_t *title_row = lv_obj_create(main_obj);
  lv_obj_set_size(title_row, lv_pct(100), lv_pct(10));
  lv_obj_align(title_row, LV_ALIGN_TOP_LEFT, 0, 5);
  lv_obj_t *label = lv_label_create(title_row);
  lv_label_set_text(label, cstr_str(&title));
  lv_obj_center(label);
};

#endif // LVGL_FILE_VIEWER_TITLE_BAR_H
