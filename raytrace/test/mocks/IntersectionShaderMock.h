#ifndef _INTERSECTIONSHADERMOCK_H_
#define _INTERSECTIONSHADERMOCK_H_

#include "CppUTestExt/GMock.h"
#include "IntersectionShader.h"

class IntersectionShaderMock : public IntersectionShader {

public:
  MOCK_METHOD3(shade, bool(float, float,RTMaterial));

};

#endif /* _INTERSECTIONSHADERMOCK_H_ */
