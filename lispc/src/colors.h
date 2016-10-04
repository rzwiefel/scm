#ifndef COLORS_H
#define COLORS_H

#include <unistd.h>

#define __color(str,code) \
  ((isatty(fileno(stdin))) ? "\033[0;"code"m"str"\033[0;0m" : str)

// text color decoration macros
#define __blue(str)     __color(str,"34")
#define __yellow(str)   __color(str,"33")
#define __green(str)    __color(str,"32")
#define __red(str)      __color(str,"31")
#define __purple(str)   __color(str,"34")

#endif
