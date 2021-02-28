CSRCS += lv_group.c
CSRCS += lv_indev.c
CSRCS += lv_disp.c
CSRCS += lv_obj.c
CSRCS += lv_refr.c
CSRCS += lv_style.c

DEPPATH += --dep-path ../lv_core
VPATH += :../lv_core

CFLAGS += "-I../lv_core"
