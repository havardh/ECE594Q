#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include "Matrix.h"
#include "Mesh.h"
#include "Sphere.h"
#include "BoundingBox.h"
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
  FrameBuffer(int, int);
  ~FrameBuffer();

  void setProjectionMatrix(Matrix &);
  void draw(Matrix *, int);
  void drawPoint(Matrix);
  void drawRectangle(int, int, int, int);
  void drawBox(BoundingBox);
  void draw(Mesh *);
  void bind(char *);
  void flush();

};


#endif /* _FRAMEBUFFER_H_ */
