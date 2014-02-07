#include "RTShape.h"
#include "Dbg.h"

void RTShape::addMaterial(RTMaterial material) {
  this->materials.push_back(material);
}

int RTShape::getMaterialCount() const {
  return (int)this->materials.size();
}

const RTMaterial RTShape::getMaterial(int i) const {
  return materials[(size_t)i];
}
