#ifndef _INTERSECTIONSHADER_H_
#define _INTERSECTIONSHADER_H_

class IntersectionShader {

public:
  virtual bool shade(float u, float v) = 0;
};

#endif /* _INTERSECTIONSHADER_H_ */
