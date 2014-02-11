#ifndef _DBG_H_
#define _DBG_H_

#include <cstdarg>
#include <stdio.h>

#define DPRINTF(...) {printf("%s: %d: ", __FILE__, __LINE__); printf(__VA_ARGS__);}

#endif /* _DBG_H_ */
