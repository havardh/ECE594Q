#ifndef _RTSHAPE_H_
#define _RTSHAPE_H_

#include "Ray.h"
#include "RTMaterial.h"
#include "Matrix.h"
#include "Intersection.h"
#include "ColorShader.h"
#include <vector>

class RTShape {
  
public:
  virtual ~RTShape() {}
  virtual IntersectionPtr intersect(const Ray ) = 0;
  virtual MatrixPtr normal(const Matrix &) = 0;

  // Materials
  void addMaterial(RTMaterial);
  virtual int getMaterialCount() const;
  virtual const RTMaterial getMaterial(int) const;
  RTMaterial* getMaterialPointer(int);

  // Shaders
  void setColorShader(ColorShader *shader);
  virtual RTMaterial shadePoint(const Matrix&) = 0;

  virtual void print() const {};

private:
  std::vector<RTMaterial> materials;

protected:
  ColorShader *_shader = 0;

};

typedef std::vector<RTShape*>::const_iterator RTShapeIter;

#endif /* _RTSHAPE_H_ */
