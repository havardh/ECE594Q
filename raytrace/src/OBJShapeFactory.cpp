#include "OBJShapeFactory.h"

RTShape* OBJShapeFactory::createShape(tinyobj::shape_t shape) {

  RTPolySet *set = new RTPolySet();


  for (int i=0; i<shape.mesh.indices.size(); i+=3) {
    RTTriangle triangle(
      Vector(
        shape.mesh.positions[shape.mesh.indices[i]*3+0],
        shape.mesh.positions[shape.mesh.indices[i]*3+1],
        shape.mesh.positions[shape.mesh.indices[i]*3+2]
      ),
      Vector(
        shape.mesh.positions[shape.mesh.indices[i+2]*3+0],
        shape.mesh.positions[shape.mesh.indices[i+2]*3+1],
        shape.mesh.positions[shape.mesh.indices[i+2]*3+2]
      ),
      Vector(
        shape.mesh.positions[shape.mesh.indices[i+1]*3+0],
        shape.mesh.positions[shape.mesh.indices[i+1]*3+1],
        shape.mesh.positions[shape.mesh.indices[i+1]*3+2]
      )
    );

    
    triangle.setHasNormals(false);    
    triangle.setHasMaterial(false);
    triangle.setParent(set);
    set->addTriangle(triangle);
  }
  set->addMaterial(createMaterial(shape.material));
  
  return set;

}

RTMaterial OBJShapeFactory::createMaterial(tinyobj::material_t m) {

  RTMaterial material;
  material.setDiffColor(RTColor(m.diffuse));
  material.setAmbColor(RTColor(m.ambient));
  material.setSpecColor(RTColor(m.specular));
  material.setEmissColor(RTColor(m.emission));
  material.setShininess(m.shininess);
  material.setKTransparency(RTColor(m.transmittance).length());

  return material;

}
