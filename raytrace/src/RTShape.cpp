#include "RTShape.h"
#include "Dbg.h"

void RTShape::addMaterial(RTMaterial material) {
  this->materials.push_back(material);
}

int RTShape::getMaterialCount() const {
  return (int)this->materials.size();
}

const RTMaterial RTShape::getMaterial(int i) const {
  if (i < this->getMaterialCount()) {
    return materials[(size_t)i];
  } else {
    return RTMaterial();
  }
}

void RTShape::setColorShader(ColorShader *shader) {
  this->_shader = shader;
}
