#ifndef _RTSHAPE_H_
#define _RTSHAPE_H_

#include "Ray.h"
#include "RTMaterial.h"
#include "Matrix.h"
#include "Intersection.h"
#include "ColorShader.h"
#include "IntersectionShader.h"
#include "BBox.h"
#include "ColorShaderTexture.h"
#include <vector>

class RTShape {
  
public:
  virtual ~RTShape();
  virtual IntersectionPtr intersect(const Ray ) = 0;
  virtual MatrixPtr normal(const Matrix &) = 0;

  // Materials
  void addMaterial(RTMaterial);
  virtual int getMaterialCount() const;
  virtual const RTMaterial getMaterial(int) const;
  RTMaterial* getMaterialPointer(int);

  // Shaders
  void setColorShader(ColorShader *shader);
  void setIntersectionShader(IntersectionShader *shader);
  ColorShader* getColorShader() { return _colorShader; }
  IntersectionShader* getIntersectionShader() { return _intersectionShader; }
  
  RTMaterial shadePoint(const Matrix&);
  bool shadeIntersection(const Intersection&);

  virtual Matrix getPosition() const = 0;
  virtual BoundingBox getBoundingBox() const = 0;

  virtual void print() const {};

  virtual void interpolateUV(float &, float &, const Matrix &) = 0;
  virtual const RTMaterial interpolateMaterial(const Matrix&) = 0;

private:
  std::vector<RTMaterial> materials;

protected:
  ColorShader *_colorShader = 0;
  IntersectionShader *_intersectionShader = 0;

};

typedef std::vector<RTShape*>::const_iterator RTShapeIter;

#endif /* _RTSHAPE_H_ */
