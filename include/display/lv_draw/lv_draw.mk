CSRCS += lv_draw_vbasic.c
CSRCS += lv_draw_rbasic.c
CSRCS += lv_draw.c
CSRCS += lv_draw_rect.c
CSRCS += lv_draw_label.c
CSRCS += lv_draw_line.c
CSRCS += lv_draw_img.c
CSRCS += lv_draw_arc.c
CSRCS += lv_draw_triangle.c

<<<<<<< HEAD
DEPPATH += --dep-path display/lv_draw
VPATH += :display/lv_draw

CFLAGS += "-Idisplay/lv_draw"
=======
DEPPATH += --dep-path $(LVGL_DIR)/lvgl/lv_draw
VPATH += :$(LVGL_DIR)/lvgl/lv_draw

CFLAGS += "-I$(LVGL_DIR)/lvgl/lv_draw"
>>>>>>> parent of bbdcf2b (new lvgl)
