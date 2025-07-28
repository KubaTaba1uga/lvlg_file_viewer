#ifndef LVGL_FILE_VIEWER_X11_DRIVER_H
#define LVGL_FILE_VIEWER_X11_DRIVER_H

#include "c_minilib_error.h"
#include "lvgl.h"
#include "utils/settings.h"
#include <src/display/lv_display.h>
#include <src/misc/lv_event.h>
#include <stdio.h>

static inline cme_error_t init_x11_driver(void) {
  lv_display_t *disp =
      lv_x11_window_create("LVGL File Viewer", SCREEN_WIDTH, SCREEN_HEIGHT);
  cme_error_t err;

  if (!disp) {
    err = cme_error(EINVAL, "Cannot initialize X11 display");
    goto error_out;
  }

  LV_IMG_DECLARE(mouse_cursor_icon);
  lv_x11_inputs_create(disp, &mouse_cursor_icon);

  return 0;

error_out:
  return cme_return(err);
};

#endif // LVGL_FILE_VIEWER_X11_DRIVER_H
