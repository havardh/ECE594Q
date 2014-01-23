#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include "Matrix.h"
#include "Mesh.h"
#include "Sphere.h"
#include "SimplePolygon.h"
#include "BoundingBox.h"
#include <string.h>

typedef struct {
  float z;
  Color color;
} Sample;

//typedef Color Sample;
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

  void set(int, int, Color);
  void set(int, int, int, Color, float);
  void set(int, int, int, Color);
  Color get(int, int) const;
  
  void setProjectionMatrix(Matrix &);
  void draw(Matrix *, int);
  void drawPoint(Matrix);
  void drawRectangle(int, int, int, int);
  void drawBox(BoundingBox);
  void drawMicropolygon(Micropolygon);
  void draw(Mesh *);
  void bind(char *);
  void flush(int );

};


#endif /* _FRAMEBUFFER_H_ */
