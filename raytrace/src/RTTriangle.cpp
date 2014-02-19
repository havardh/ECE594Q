#include "RTTriangle.h"
#include "Dbg.h"
#include <stdlib.h>

#define EPSILON 0.00001

RTTriangle::RTTriangle(const Vector &p0, const Vector &p1, const Vector &p2, const Vector &n0, const Vector &n1, const Vector &n2) {
  _p0 = p0;
  _p1 = p1;
  _p2 = p2;

  _n0 = n0;
  _n1 = n1;
  _n2 = n2;
  _hasNormals = true;
  _parent = 0;
}

RTTriangle::RTTriangle(const Vector &p0, const Vector &p1, const Vector &p2) {
  _p0 = p0;
  _p1 = p1;
  _p2 = p2;


  _n0 = Vector(0,0,0);
  _n1 = Vector(0,0,0);
  _n2 = Vector(0,0,0);

  _hasNormals = false;
  _parent = 0;
}
// http://www.cs.virginia.edu/~gfx/Courses/2003/ImageSynthesis/papers/Acceleration/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
IntersectionPtr RTTriangle::intersect(const Ray ray) {

  Vector orig = ray.getOrigin();
  Vector dir = ray.getDirection();

  Vector edge1 = _p1 - _p0;
  Vector edge2 = _p2 - _p0;

  Vector pvec = dir.cross(edge2);

  float det = edge1.dot(pvec);

  if (det > -EPSILON && det < EPSILON) 
    return IntersectionPtr(NULL);
  float inv_det = 1 / det;

  Vector tvec = orig - _p0;

  float u = tvec.dot(pvec) * inv_det;
  if (u < 0.0 || u > 1.0) {
    return IntersectionPtr(NULL);
  }

  Vector qvec = tvec.cross(edge1);

  float v = dir.dot(qvec) * inv_det;
  if (v < 0.0 || u + v > 1.0) 
    return IntersectionPtr(NULL);
  

  float t = edge2.dot(qvec) *inv_det;

  if ( t > 0 ) {
    Vector point(orig + t * dir);

    if (fabs((ray.getOrigin() - point).length()) < 0.001) {
      return IntersectionPtr(NULL);
    } else {
      return IntersectionPtr(new Intersection(this, ray, point));
    }
  } else {
    return IntersectionPtr(NULL);
  }

}

float area(const Vector &A, const Vector &B, const Vector &C) {

  Vector AB = B-A;
  Vector AC = C-A;
  
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

VectorPtr RTTriangle::interpolateNormal(const Vector &point) {

  float A = area(_p0, _p1, _p2);
  float A0 = area(point, _p1, _p2);
  float A1 = area(point, _p0, _p2);
  float A2 = area(point, _p0, _p1);

  Vector *m = new Vector(0,0,0);
  (*m) = (*m) + _n0 * (A0/A);
  (*m) = (*m) + _n1 * (A1/A);
  (*m) = (*m) + _n2 * (A2/A);
  
  m->normalize();

  return VectorPtr(m);
}

VectorPtr RTTriangle::calculateNormal(const Vector &point) {
  Vector v1 = _p1 - _p0;
  Vector v2 = _p2 - _p0;
 
  Vector direction = v2.cross(v1);
 
  if (_parent) {
    Vector fromMid = point - _parent->getMidpoint();
  

    if ( direction.dot(fromMid) < 0 ) {
      direction = -direction;
    }
  }
  return VectorPtr(new Vector(direction.normalize()));

}

VectorPtr RTTriangle::normal(const Vector &point) {

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

void RTTriangle::interpolateUV(float &u, float &v, const Vector point) {
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

const RTMaterial RTTriangle::interpolateMaterial(const Vector &point) {

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

float max(float x0, float x1, float x2) {
  return (x0 > x1 ? (x0 > x2 ? x0 : (x1 > x2 ? x1 : x2)) : (x1 > x2 ? x1 : x2));
}

float min(float x0, float x1, float x2) {
  return (x0 < x1 ? (x0 < x2 ? x0 : (x1 < x2 ? x1 : x2)) : (x1 < x2 ? x1 : x2));  
}

BoundingBox RTTriangle::getBoundingBox() const {
  float x0 = min(_p0.x(), _p1.x(), _p2.x());
  float y0 = min(_p0.y(), _p1.y(), _p2.y());
  float z0 = min(_p0.z(), _p1.z(), _p2.z());

  float x1 = max(_p0.x(), _p1.x(), _p2.x());
  float y1 = max(_p0.y(), _p1.y(), _p2.y());
  float z1 = max(_p0.z(), _p1.z(), _p2.z());

  Vector origin(x0,y0,z0);
  Vector delta(x1-x0, y1-y0, z1-z0);

  return BoundingBox(origin, delta);
}
