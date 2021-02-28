CSRCS += lv_theme.c

CSRCS += lv_theme_empty.c
CSRCS += lv_theme_material.c
CSRCS += lv_theme_mono.c
CSRCS += lv_theme_template.c

DEPPATH += --dep-path display/lv_themes
VPATH += :display/lv_themes

CFLAGS += "-Idisplay/lv_themes"
