#include "RTTriangle.h"
#include "Dbg.h"
#include <stdlib.h>

#define EPSILON 0.00001

RTTriangle::RTTriangle(const Matrix &p0, const Matrix &p1, const Matrix &p2, const Matrix &n0, const Matrix &n1, const Matrix &n2) {
  _p0 = p0;
  _p1 = p1;
  _p2 = p2;

  _n0 = n0;
  _n1 = n1;
  _n2 = n2;
  _hasNormals = true;
  _parent = 0;
}

RTTriangle::RTTriangle(const Matrix &p0, const Matrix &p1, const Matrix &p2) {
  _p0 = p0;
  _p1 = p1;
  _p2 = p2;


  _n0 = Matrix(0,0,0);
  _n1 = Matrix(0,0,0);
  _n2 = Matrix(0,0,0);

  _hasNormals = false;
  _parent = 0;
}
// http://www.cs.virginia.edu/~gfx/Courses/2003/ImageSynthesis/papers/Acceleration/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
IntersectionPtr RTTriangle::intersect(const Ray ray) {

  Matrix orig = ray.getOrigin();
  Matrix dir = ray.getDirection();

  Matrix edge1 = _p1 - _p0;
  Matrix edge2 = _p2 - _p0;

  Matrix pvec = dir.crossProduct(edge2);

  float det = edge1.dot(pvec);

  if (det > -EPSILON && det < EPSILON) 
    return IntersectionPtr(NULL);
  float inv_det = 1 / det;

  Matrix tvec = orig - _p0;

  float u = tvec.dot(pvec) * inv_det;
  if (u < 0.0 || u > 1.0) {
    return IntersectionPtr(NULL);
  }

  Matrix qvec = tvec.crossProduct(edge1);

  float v = dir.dot(qvec) * inv_det;
  if (v < 0.0 || u + v > 1.0) 
    return IntersectionPtr(NULL);
  

  float t = edge2.dot(qvec) *inv_det;

  if ( t > 0 ) {
    Matrix point(orig + t * dir);

    if (fabs((ray.getOrigin() - point).length()) < 0.001) {
      return IntersectionPtr(NULL);
    } else {
      return IntersectionPtr(new Intersection(this, ray, point));
    }
  } else {
    return IntersectionPtr(NULL);
  }

}

float area(const Matrix &A, const Matrix &B, const Matrix &C) {

  Matrix AB = B-A;
  Matrix AC = C-A;
  
  float ABlen = AB.length();
  float AClen = AC.length();
  

  if ((ABlen * AClen) < 0.00001) {
    return 0;
  }
  
  if (fabs(AB.dot(AC) / (ABlen * AClen)) > 1) {
    return 0;
  }
  
  float angle = acos(AB.dot(AC) / (ABlen * AClen));

  return 0.5 * ABlen*AClen * sin(angle);

}

MatrixPtr RTTriangle::interpolateNormal(const Matrix &point) {

  float A = area(_p0, _p1, _p2);
  float A0 = area(point, _p1, _p2);
  float A1 = area(point, _p0, _p2);
  float A2 = area(point, _p0, _p1);

  Matrix *m = new Matrix(0,0,0);
  (*m) = (*m) + _n0 * (A0/A);
  (*m) = (*m) + _n1 * (A1/A);
  (*m) = (*m) + _n2 * (A2/A);
  
  m->normalize();

  return MatrixPtr(m);
}

MatrixPtr RTTriangle::calculateNormal(const Matrix &point) {
  Matrix v1 = _p1 - _p0;
  Matrix v2 = _p2 - _p0;
 
  Matrix direction = v2.crossProduct(v1);
 
  if (_parent) {
    Matrix fromMid = point - _parent->getMidpoint();
  

    if ( direction.dot(fromMid) < 0 ) {
      direction = -direction;
    }
  }
  return MatrixPtr(new Matrix(direction.normalize()));

}

MatrixPtr RTTriangle::normal(const Matrix &point) {

  if (hasNormals()) {
    return interpolateNormal(point);
  } else {
    return calculateNormal(point);
  }

}

const RTMaterial RTTriangle::getMaterial(int i) const {
  if (_parent) {
    return _parent->getMaterial(i);
  } else {
    return RTMaterial();
  }
}

int RTTriangle::getMaterialCount() const {
  if (_parent) {
    return _parent->getMaterialCount();
  } else {
    return 0;
  }
}

void RTTriangle::interpolateUV(float &u, float &v, const Matrix &point) {
  float A = area(_p0, _p1, _p2);
  float A0 = area(point, _p1, _p2);
  float A1 = area(point, _p0, _p2);
  float A2 = area(point, _p0, _p1);

  // u and v values for each coorner
  float u0, u1, u2, v0, v1, v2;
  if (this->_isUpper) {
    u0 = 0; v0 = 0;
    u1 = 1; v1 = 0;
    u2 = 0; v2 = 1;
  } else {
    u0 = 1; v0 = 1;
    u1 = 1; v1 = 0;
    u2 = 0; v2 = 1;
  }

  u =  u0 * (A0/A);
  u += u1 * (A1/A);
  u += u2 * (A2/A);

  v =  v0 * (A0/A);
  v += v1 * (A1/A);
  v += v2 * (A2/A);
}

const RTMaterial RTTriangle::interpolateMaterial(const Matrix &point) {

  if (_hasMaterial) {
    float A = area(_p0, _p1, _p2);
    float A0 = area(point, _p1, _p2);
    float A1 = area(point, _p0, _p2);
    float A2 = area(point, _p0, _p1);

    RTMaterial material;
    material += (*_m0) * (A0 / A); 
    material += (*_m1) * (A1 / A);
    material += (*_m2) * (A2 / A);

    return material;
  }
  return getMaterial(0);
}
