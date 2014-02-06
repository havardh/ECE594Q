#ifndef _RTSHAPE_H_
#define _RTSHAPE_H_

#include "Ray.h"
#include "RTMaterial.h"
#include "Matrix.h"
#include <vector>

class RTShape {
  
public:
  virtual ~RTShape() {}
  virtual MatrixPtr intersect(const Ray ) = 0;
  virtual MatrixPtr normal(const Matrix &, const Matrix &) = 0;

  void addMaterial(RTMaterial);
  int getMaterialCount() const;
  const RTMaterial getMaterial(int) const;

private:
  std::vector<RTMaterial> materials;
  

};

typedef std::vector<RTShape*>::const_iterator RTShapeIter;

#endif /* _RTSHAPE_H_ */
