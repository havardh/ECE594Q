#ifndef _MICROPOLYGON_H_
#define _MICROPOLYGON_H_

#include "Matrix.h"
#include "BoundingBox.h"
#include "Color.h"

class Polygon {

private:
  Matrix *_points[4];

  Color _color;
  float _opacity;

  void allocate();
  
public:
  Polygon();
  Polygon(Matrix ** points);

  Matrix* get(int i) const;
  float getOpacity() const { return _opacity; }
  void setOpacity(float opacity) { _opacity = opacity; }
  void set(int i, Matrix*);
  BoundingBox getBoundingBox() const;

  void setColor(Color);
  Color getColor() const;

  bool intersects(float, float);

  void print() { 
    for (int i=0; i<4; i++) {
      _points[i]->printPoint();
    }
  }
  
};

#endif /* _MICROPOLYGON_H_ */
