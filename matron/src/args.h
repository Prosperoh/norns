#pragma once

#include <stdbool.h>

extern int args_parse(int argc, char **argv);

extern const char *args_local_port(void);
extern const char *args_ext_port(void);
extern const char *args_crone_port(void);
extern const char *args_monome_path(void);
extern const char *args_framebuffer(void);
extern bool args_skip_ioctls(void);
extern const char *args_gpio(void);
