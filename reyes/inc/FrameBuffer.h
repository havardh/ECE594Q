#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include "Bmp.h"
#include "Matrix.h"

class FrameBuffer {

private:
  int _width, _height;
  char *_filename;
  unsigned char *buffer;
  Matrix _projectionMatrix;

public:
  FrameBuffer(int width, int height);
  ~FrameBuffer();

  void setProjectionMatrix(Matrix &);
  void draw(Matrix * points, int n);
  void bind(char *filename);
  void flush();

};


#endif /* _FRAMEBUFFER_H_ */
