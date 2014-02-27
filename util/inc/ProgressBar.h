#ifndef _PROGRESSBAR_H_
#define _PROGRESSBAR_H_

#include <pthread.h>
#include <stdio.h>
#include "Dbg.h"

void ProgressBar_setMax(int);
void ProgressBar_tick();
void ProgressBar_report();
void ProgressBar_printBar(int);

#endif /* _PROGRESSBAR_H_ */
