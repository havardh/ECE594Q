#include "OBJShapeFactory.h"

RTShape* OBJShapeFactory::createShape(tinyobj::shape_t shape) {

  RTPolySet *set = new RTPolySet();


  int j=0;
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

    triangle.setN0(&shape.mesh.normals[shape.mesh.indices[i+0]*3+0]);
    triangle.setN1(&shape.mesh.normals[shape.mesh.indices[i+2]*3+0]);
    triangle.setN2(&shape.mesh.normals[shape.mesh.indices[i+1]*3+0]);
    
    triangle.setHasNormals(true);    
    triangle.setHasMaterial(false);
    triangle.setParent(set);
    triangle.setIsUpper(j++ % 2 == 0);
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
