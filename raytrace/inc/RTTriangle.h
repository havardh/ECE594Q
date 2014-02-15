#ifndef _RTTRIANGLE_H_
#define _RTTRIANGLE_H_

#include <cmath>
#include "Matrix.h"
#include "RTShape.h"
#include "RTPolySet.h"
#include "Dbg.h"

class RTPolySet;
class RTTriangle : public RTShape {

public:
  RTTriangle() {}
  RTTriangle(
    const Matrix &, const Matrix &, const Matrix &
  );
  RTTriangle(
    const Matrix &, const Matrix &, const Matrix &,
    const Matrix &, const Matrix &, const Matrix &
  );
  virtual IntersectionPtr intersect(const Ray );
  virtual MatrixPtr normal(const Matrix &);
  virtual Matrix getPosition() const { return _p0; }
  virtual BoundingBox getBoundingBox() const;

  virtual int getMaterialCount() const;
  virtual const RTMaterial getMaterial(int) const;

  void setP0(Matrix m) { _p0 = m; }
  const Matrix getP0() const { return _p0; }
  void setP1(Matrix m) { _p1 = m; } 
  const Matrix getP1() const { return _p1; }
  void setP2(Matrix m) { _p2 = m; }
  const Matrix getP2() const { return _p2; }

  void setN0(Matrix m) { _n0 = m; } 
  const Matrix getN0() const { return _n0; }
  void setN1(Matrix m) { _n1 = m; } 
  const Matrix getN1() const { return _n1; }
  void setN2(Matrix m) { _n2 = m; }
  const Matrix getN2() const { return _n2; }

  void setM0(RTMaterial *m) { _m0 = m; }
  RTMaterial* getM0() { return _m0; }
  void setM1(RTMaterial *m) { _m1 = m; }
  RTMaterial* getM1() { return _m1; }
  void setM2(RTMaterial *m) { _m2 = m; }
  RTMaterial* getM2() { return _m2; }

  virtual void print() const { 
    DPRINTF("Triangle\n"); 
    _p0.printPoint(); 
    _p1.printPoint();  
    _p2.printPoint();
  }
  void setParent(RTPolySet *parent) {
    _parent = parent;
  }
  void setIsUpper(bool isUpper) {
    _isUpper = isUpper;
  }
  void setHasMaterial(bool hasMaterial) {
    _hasMaterial = hasMaterial;
  }
  void setHasNormals(bool hasNormals) {
    _hasNormals = hasNormals;
  }

  virtual void interpolateUV(float &u, float &v, const Matrix point);
  virtual const RTMaterial interpolateMaterial(const Matrix&);

  virtual int getID() { return RTTriangle::shapeID; }
  const static int shapeID = 3;

private:
  RTPolySet *_parent;

  // In the texture in parameterization a quad is processed
  // This implies a relationship between two triangles
  // This variable lets the shader know which of the two its operating on
  bool _isUpper = 0;

  // Does the triangle have normals at the vertices
  bool _hasNormals = 0;

  // Does the triangle have materials at the vertices
  bool _hasMaterial = 0;

  Matrix _p0, _p1, _p2;
  Matrix _n0, _n1, _n2;
  RTMaterial *_m0, *_m1, *_m2;

  Matrix computeN();
  Matrix computeP(Matrix&, Matrix, Matrix);

  bool hasNormals() { return _hasNormals; }
  MatrixPtr calculateNormal(const Matrix&);
  MatrixPtr interpolateNormal(const Matrix&);

};

#endif /* _RTTRIANGLE_H_ */
