CSRCS += lv_hal_disp.c
CSRCS += lv_hal_indev.c
CSRCS += lv_hal_tick.c

DEPPATH += --dep-path display/lv_hal
VPATH += :display/lv_hal

CFLAGS += "-Idisplay/lv_hal"
