#ifndef _RTSHAPEMOCK_H_
#define _RTSHAPEMOCK_H_

#include "CppUTestExt/GMock.h"
#include "Matrix.h"
#include "RTMaterial.h"
#include "Intersection.h"

class RTShapeMock : public RTShape {
public:
  MOCK_CONST_METHOD0(getMaterialCount, int());
  MOCK_CONST_METHOD1(getMaterial, const RTMaterial(int));
  MOCK_METHOD1(shadePoint, RTMaterial(const Matrix&));
  MOCK_METHOD1(intersect, IntersectionPtr(const Ray));
  MOCK_METHOD2(normal, MatrixPtr(const Matrix&, const Matrix&));
  MOCK_METHOD0(print, void());
};

#endif /* _RTSHAPEMOCK_H_ */
