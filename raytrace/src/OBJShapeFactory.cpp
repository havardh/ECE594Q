#include "OBJShapeFactory.h"

RTShape* OBJShapeFactory::createShape(tinyobj::shape_t shape) {

  RTPolySet *set = new RTPolySet();

  int j=0;
  for (int i=0; i<shape.mesh.positions.size(); i+=4) {
    if (j++ % 2 == 0) {

      RTTriangle triangle(
        Vector(
          shape.mesh.positions[i+0],
          shape.mesh.positions[i+1],
          shape.mesh.positions[i+2]
        ),
        Vector(
          shape.mesh.positions[i+3],
          shape.mesh.positions[i+4],
          shape.mesh.positions[i+5]
        ),
        Vector(
          shape.mesh.positions[i+9],
          shape.mesh.positions[i+10],
          shape.mesh.positions[i+11]
        )
      );
      triangle.setHasNormals(false);    
      triangle.setHasMaterial(false);
      triangle.setParent(set);
      triangle.setIsUpper(true);
      set->addTriangle(triangle);
    } else {
      RTTriangle triangle(
        Vector(
          shape.mesh.positions[i+0],
          shape.mesh.positions[i+1],
          shape.mesh.positions[i+2]
        ),
        Vector(
          shape.mesh.positions[i+6],
          shape.mesh.positions[i+7],
          shape.mesh.positions[i+8]
        ),
        Vector(
          shape.mesh.positions[i+9],
          shape.mesh.positions[i+10],
          shape.mesh.positions[i+11]
        )
      );
      triangle.setHasNormals(false);    
      triangle.setHasMaterial(false);
      triangle.setParent(set);
      triangle.setIsUpper(true);
      set->addTriangle(triangle);
    }
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
