#pragma once

#ifdef DEBUG
#include <stdio.h>
#define debug(fmt, ...) fprintf(stdout, "<%s:%d> " fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif
