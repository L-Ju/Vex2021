CSRCS += lv_hal_disp.c
CSRCS += lv_hal_indev.c
CSRCS += lv_hal_tick.c

<<<<<<< HEAD
DEPPATH += --dep-path display/lv_hal
VPATH += :display/lv_hal

CFLAGS += "-Idisplay/lv_hal"
=======
DEPPATH += --dep-path $(LVGL_DIR)/lvgl/lv_hal
VPATH += :$(LVGL_DIR)/lvgl/lv_hal

CFLAGS += "-I$(LVGL_DIR)/lvgl/lv_hal"
>>>>>>> parent of bbdcf2b (new lvgl)
