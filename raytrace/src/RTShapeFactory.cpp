#include "RTShapeFactory.h"

RTTriangle RTShapeFactory::createTriangle(PolygonIO *polygon) {

    return RTTriangle(
      Matrix(polygon->vert[0].pos), 
      Matrix(polygon->vert[1].pos), 
      Matrix(polygon->vert[2].pos)
    );
}

RTShape* RTShapeFactory::createShape(ObjIO *obj) {
  
  (void) obj;

  if (obj->type == SPHERE_OBJ) {

    SphereIO *io = (SphereIO*)obj->data;
    return new RTSphere(io->origin, io->radius);

  } else if (obj->type == POLYSET_OBJ) {

    RTPolySet *set = new RTPolySet();
    PolySetIO *io = (PolySetIO*)obj->data;
    for (int i=0; i<io->numPolys; i++) {
      RTTriangle t = RTShapeFactory::createTriangle(&io->poly[i]);
      set->addTriangle(t);
    }
    return set;

  }

  return NULL;
}
