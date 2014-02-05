#ifndef _RAYFRAMEBUFFER_H_
#define _RAYFRAMEBUFFER_H_

#include <stdint.h>

class RayFrameBuffer {

private:
  uint8_t *_frameBuffer;
  int _width, _height;
  
  void allocate();

public:
  RayFrameBuffer(int, int);
  ~RayFrameBuffer();

  void set(int,int,int,uint8_t);
  uint8_t get(int, int, int) const;
  int getWidth() const { return _width; }
  int getHeight() const { return _height; }
  void write(const char*);

};

#endif /* _RAYFRAMEBUFFER_H_ */
