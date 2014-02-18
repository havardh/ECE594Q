#ifndef _RTSHAPEMOCK_H_
#define _RTSHAPEMOCK_H_

#include "CppUTestExt/GMock.h"
#include "Vector.h"
#include "RTMaterial.h"
#include "Intersection.h"

class RTShapeMock : public RTShape {
public:
  MOCK_CONST_METHOD0(getMaterialCount, int());
  MOCK_CONST_METHOD1(getMaterial, const RTMaterial(int));
  MOCK_METHOD1(shadePoint, RTMaterial(const Vector&));
  MOCK_METHOD1(shadeIntersection, bool(const Intersection&));
  MOCK_METHOD1(intersect, IntersectionPtr(const Ray));
  MOCK_CONST_METHOD0(getPosition, Vector());
  MOCK_CONST_METHOD0(getBoundingBox, BoundingBox());
  MOCK_METHOD1(normal, VectorPtr(const Vector&));
  MOCK_METHOD0(print, void());

  MOCK_METHOD3(interpolateUV, void(float&, float&, const Vector));
  MOCK_METHOD1(interpolateMaterial, const RTMaterial(const Vector&));
};

#endif /* _RTSHAPEMOCK_H_ */
