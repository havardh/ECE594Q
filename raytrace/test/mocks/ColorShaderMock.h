#ifndef _COLORSHADERMOCK_H_
#define _COLORSHADERMOCK_H_

#include "CppUTestExt/GMock.h"
#include "ColorShader.h"

class ColorShaderMock : public ColorShader {

public: 
MOCK_METHOD3(shade, RTMaterial(float,float,RTMaterial));

};

#endif /* _COLORSHADERMOCK_H_ */
