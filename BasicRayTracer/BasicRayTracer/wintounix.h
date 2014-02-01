#ifndef _WINTOUNIX_H_
#define _WINTOUNIX_H_

#include <stdio.h>
#include <string.h>

#define DWORD unsigned int
#define LONG unsigned int
#define LONGLONG unsigned long int

typedef union _LARGE_INTEGER {
  struct {
    DWORD LowPart;
    LONG  HighPart;
  };
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

bool QueryPerformanceFrequency(PLARGE_INTEGER n);
bool QueryPerformanceCounter(PLARGE_INTEGER n);
void fopen_s(FILE** fb, const char* filename, const char* mode);

char * _strdup(char * str);

#endif /* _WINTOUNIX_H_ */
