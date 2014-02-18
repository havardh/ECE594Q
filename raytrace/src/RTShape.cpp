#include "RTShape.h"
#include "Dbg.h"

RTShape::~RTShape() {

  if (typeid(ColorShaderTexture) == typeid(_colorShader)) {
    delete (ColorShaderTexture*)_colorShader;
  }

}

void RTShape::addMaterial(RTMaterial material) {
  this->materials.push_back(material);
}

int RTShape::getMaterialCount() const {
  return (int)this->materials.size();
}

RTMaterial* RTShape::getMaterialPointer(int i) {
  if (i < this->getMaterialCount()) {
    return &materials[(size_t)i];
  } else {
    return 0;
  }
}

const RTMaterial RTShape::getMaterial(int i) const {
  if (i < this->getMaterialCount()) {
    return materials[(size_t)i];
  } else {
    return RTMaterial();
  }
}

void RTShape::setColorShader(ColorShader *shader) {
  this->_colorShader = shader;
}


void RTShape::setIntersectionShader(IntersectionShader *shader) {
  this->_intersectionShader = shader;
}

RTMaterial RTShape::shadePoint(const Vector &point) {

  if (getColorShader()) {

    float u,v;
    interpolateUV(u, v, point);
    RTMaterial material = interpolateMaterial(point);

    return getColorShader()->shade(u, v, material);
  }

  return getMaterial(0);
}


bool RTShape::shadeIntersection(const Intersection &intersection) {

  if (getIntersectionShader()) {
    
    float u,v;
    interpolateUV(u,v, intersection.getPoint());

    return getIntersectionShader()->shade(u,v, getMaterial(0));

  }
  return true;
}

