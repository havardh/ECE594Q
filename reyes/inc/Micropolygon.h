#ifndef _MICROPOLYGON_H_
#define _MICROPOLYGON_H_

#include "Matrix.h"
#include "BoundingBox.h"
#include "Color.h"

class Micropolygon {

protected:  
  Matrix _points[4];

private:

  Color _color;

  void allocate();
  
public:
  Micropolygon();
  Micropolygon(Matrix * points);

  Matrix get(int i) const;
  void set(int i, Matrix);
  BoundingBox getBoundingBox() const;

  void setColor(Color);
  Color getColor() const;

  bool intersects(float, float);

  void print() { 
    for (int i=0; i<4; i++) {
      _points[i].printPoint();
    }
  }
  
};

#endif /* _MICROPOLYGON_H_ */
