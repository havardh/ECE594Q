#include "Dbg.h"

void dprintf(const char * fmt, ...) {

  va_list args;
  va_start(args, fmt);
  printf("%s:%d ", __FILE__, __LINE__);
  printf(fmt, args);
  va_end(args);

}

