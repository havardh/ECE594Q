#include "RTTriangle.h"

#define EPSILON 0.0000001

RTTriangle::RTTriangle(const Matrix &p0, const Matrix &p1, const Matrix &p2) {
  _p0 = p0;
  _p1 = p1;
  _p2 = p2;
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
  if (u < 0.0 || u > 1.0) 
    return IntersectionPtr(NULL);

  Matrix qvec = tvec.crossProduct(edge1);

  float v = dir.dot(qvec) * inv_det;
  if (v < 0.0 || u + v > 1.0) 
    return IntersectionPtr(NULL);

  float t = edge2.dot(qvec) *inv_det;

  IntersectionPtr intersection(new Intersection(this, ray, Matrix(orig + t * dir)));
  return intersection;

}

MatrixPtr RTTriangle::normal(const Matrix &point, const Matrix &from ) {
  (void) point; (void) from;
  
  Matrix v1 = _p1 - _p0;
  Matrix v2 = _p2 - _p0;

  Matrix direction = v2.crossProduct(v1);

  if ( direction.dot(from) < 0 ) {
    direction = -direction;
  }

  return MatrixPtr(new Matrix(direction.normalize()));
}
