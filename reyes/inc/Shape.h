#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Color.h"
#include "Mesh.h"
#include <assert.h>

class Shape : public Mesh {

private:

public:
  Shape() : Mesh(800,800) {
    setColor(255, 255, 255);
  }

};

#endif /* _SHAPE_H_ */
