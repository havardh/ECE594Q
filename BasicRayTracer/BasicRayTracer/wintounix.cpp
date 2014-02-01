#include "wintounix.h"

bool QueryPerformanceFrequency(PLARGE_INTEGER n) {
  n->QuadPart = 0;
  return 0;
}

bool QueryPerformanceCounter(PLARGE_INTEGER n) {
  n->QuadPart = 0;
  return 0;
}

void fopen_s(FILE** fb, const char* filename, const char* mode) {

  *fb = fopen(filename, mode);

}

char * _strdup(char * str) {
  printf("wat\n");
  return strdup(str);
}
