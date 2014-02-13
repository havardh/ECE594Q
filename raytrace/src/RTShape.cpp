#include "RTShape.h"
#include "Dbg.h"

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
