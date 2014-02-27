#include "ProgressBar.h"

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static int max=0;
static int count=0;

void ProgressBar_setMax(int m) {
  max = m;
}

void ProgressBar_tick() {
  
  pthread_mutex_lock(&lock);
  count++;
  pthread_mutex_unlock(&lock);

  ProgressBar_report();
}

void ProgressBar_report() {
  int prev = (int)(((count-1) / (float)max) * 100);
  int curr = (int)((count / (float)max) * 100);
  if ( prev < curr ) {
    ProgressBar_printBar(curr);
  }
}

void ProgressBar_printBar(int progress) {

  printf("|");
  for (int i=0; i<progress; i+=2) {
    printf("-");
  }
  for (int i=progress+1; i<100; i+=2) {
    printf(".");
  }
  printf("| %d / 100\n", progress);

}
