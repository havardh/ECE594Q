#ifndef _RAYFRAMEBUFFER_H_
#define _RAYFRAMEBUFFER_H_

#include <stdint.h>

class RayFrameBuffer {

private:
  uint8_t *_frameBuffer;
  int _width, _height;

public:
  RayFrameBuffer(uint8_t *, int, int);

  void write(const char*);

};

#endif /* _RAYFRAMEBUFFER_H_ */
