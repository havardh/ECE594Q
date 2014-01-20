#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include "Matrix.h"
#include "Mesh.h"
#include "Sphere.h"
#include <string.h>

typedef Color Sample;
typedef Sample* Pixel;

class FrameBuffer {

private:
  int _width, _height;
  char *_filename;
  Pixel *buffer;
  Matrix _projectionMatrix;

public:
  FrameBuffer(int width, int height);
  ~FrameBuffer();

  void setProjectionMatrix(Matrix &);
  void draw(Matrix * points, int n);
  void drawPoint(Matrix);
  void draw(Mesh * mesh);
  void bind(char *filename);
  void flush();

};


#endif /* _FRAMEBUFFER_H_ */
