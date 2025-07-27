#ifndef LVGL_FILE_VIEWER_READING_AREA_H
#define LVGL_FILE_VIEWER_READING_AREA_H

#include "c_minilib_error.h"
#include "lvgl.h"
#include "stc/cstr.h"
#include "utils/settings.h"
#include <src/misc/lv_area.h>

const char *long_text =
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
    "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. "
    "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi "
    "ut aliquip ex ea commodo consequat. Duis aute irure dolor in "
    "reprehenderit "
    "in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur "
    "sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt "
    "mollit anim id est laborum. Curabitur pretium tincidunt lacus. Nulla "
    "gravida "
    "orci a odio. Nullam varius, turpis et commodo pharetra, est eros bibendum "
    "elit, "
    "nec luctus magna felis sollicitudin mauris. Integer in mauris eu nibh "
    "euismod "
    "gravida. Duis ac tellus et risus vulputate vehicula. Donec lobortis risus "
    "a elit. "
    "Etiam tempor. Ut ullamcorper, ligula eu tempor congue, eros est euismod "
    "turpis, "
    "id tincidunt sapien risus a quam. Maecenas fermentum consequat mi. Donec "
    "fermentum. "
    "Pellentesque malesuada nulla a mi. Duis sapien sem, aliquet nec, commodo "
    "eget, "
    "consequat quis, neque. Aliquam faucibus, elit ut dictum aliquet, felis "
    "nisl adipiscing "
    "sapien, sed malesuada diam lacus eget erat. Cras mollis scelerisque nunc. "
    "Nullam arcu. "
    "Aliquam consequat. Curabitur augue lorem, dapibus quis, laoreet et, "
    "pretium ac, nisi. "
    "Aenean magna nisl, mollis quis, molestie eu, feugiat in, orci. In hac "
    "habitasse platea "
    "dictumst. Fusce convallis, mauris imperdiet gravida bibendum, nisl turpis "
    "suscipit mauris, "
    "sed placerat ipsum urna sed risus. Class aptent taciti sociosqu ad litora "
    "torquent per "
    "conubia nostra, per inceptos himenaeos. Etiam nonummy nibh euismod "
    "tincidunt ut laoreet "
    "dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis "
    "nostrud exerci tation "
    "ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. "
    "Duis autem vel eum "
    "iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel "
    "illum dolore eu "
    "feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim "
    "qui blandit praesent "
    "luptatum zzril delenit augue duis dolore te feugait nulla facilisi.";

void show_reading_area(lv_obj_t *main_obj) {
  lv_obj_t *reading_area = lv_obj_create(main_obj);
  lv_obj_set_size(reading_area, SCREEN_WIDTH - 50, lv_pct(85));
  lv_obj_align(reading_area, LV_ALIGN_TOP_LEFT, 0, 5);
};

#endif // LVGL_FILE_VIEWER_READING_AREA_H
