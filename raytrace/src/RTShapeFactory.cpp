#include "RTShapeFactory.h"
#include "Dbg.h"

static ColorShaderRandom rShader;
static ColorShaderGradient gShader;
static ColorShaderCheckerboard cShader(40,40);
static ColorShaderTexture tShader("earth.jpg");
static ColorShaderIdentity iShader;

static IntersectionShaderCheckerboard intersectionShaderCheckerboard(10, 10);
static IntersectionShaderColor intersectionShaderColor;

RTTriangle RTShapeFactory::createTriangle(PolygonIO *polygon, bool hasNormals, bool hasMaterials, RTPolySet *parent) {

  RTTriangle triangle(
    Vector(polygon->vert[0].pos), 
    Vector(polygon->vert[1].pos), 
    Vector(polygon->vert[2].pos)
  );
  triangle.setParent(parent);

  if (hasNormals) {
    triangle.setHasNormals(true);
    triangle.setN0(polygon->vert[0].norm);
    triangle.setN1(polygon->vert[1].norm);
    triangle.setN2(polygon->vert[2].norm);
  }

  if (hasMaterials) {
    triangle.setHasMaterial(true);
    triangle.setM0(parent->getMaterialPointer(polygon->vert[0].materialIndex));
    triangle.setM1(parent->getMaterialPointer(polygon->vert[1].materialIndex));
    triangle.setM2(parent->getMaterialPointer(polygon->vert[2].materialIndex));
  }

  return triangle;
}

void addMaterials(RTShape*, ObjIO*);


RTShape* RTShapeFactory::createShape(ObjIO *obj) {
  
  RTShape *shape = NULL;

  if (obj->type == SPHERE_OBJ) {

    shape = createSphere(obj);

  } else if (obj->type == POLYSET_OBJ) {

    shape = createPolySet(obj);

  }

  return shape;
}

RTSphere * RTShapeFactory::createSphere(ObjIO* obj) {
  SphereIO *io = (SphereIO*)obj->data;
  RTSphere *sphere = new RTSphere(io->origin, io->radius);
  addMaterials(sphere, obj);
  //sphere->setColorShader(&tShader);
  if (obj->name) {
    ColorShaderTexture *shader = new ColorShaderTexture(obj->name);
    sphere->setColorShader(shader);
  }

  //sphere->setIntersectionShader(&intersectionShaderCheckerboard);
  return sphere;
}

RTPolySet* RTShapeFactory::createPolySet(ObjIO *obj) {

  RTPolySet *set = new RTPolySet();
  addMaterials(set, obj);
  set->setColorShader(&iShader);
  PolySetIO *io = (PolySetIO*)obj->data;

  int j = 0; // setting the is upper property for triangles
  for (int i=0; i<io->numPolys; i++) {
    RTTriangle t = RTShapeFactory::createTriangle(
      &io->poly[i],
      io->normType == PER_VERTEX_NORMAL,
      io->materialBinding == PER_VERTEX_MATERIAL,
      set
    );
    t.setIsUpper(j++ % 2 == 0);
    set->addTriangle(t);
  }

  set->calculateMidpoint();
  return set;
}

void addMaterials(RTShape *shape, ObjIO *obj) {
  for (int i=0; i<obj->numMaterials; i++) {
    shape->addMaterial(RTShapeFactory::createMaterial(&obj->material[i]));
  }
}

RTMaterial RTShapeFactory::createMaterial(MaterialIO *materialIO) {
  
  (void) materialIO;
  RTMaterial material;
  material.setDiffColor(RTColor(materialIO->diffColor));
  material.setAmbColor(RTColor(materialIO->ambColor));
  material.setSpecColor(RTColor(materialIO->specColor));
  material.setEmissColor(RTColor(materialIO->emissColor));
  material.setShininess(materialIO->shininess);
  material.setKTransparency(materialIO->ktran);
  return material;
}

RTPlane RTShapeFactory::createPlane(BoundingBox box, int axis, float pos) {

  RTPlane plane;

  float x = box.getOrigin().x();
  float y = box.getOrigin().y();
  float z = box.getOrigin().z();

  float dx = box.getDelta().x();
  float dy = box.getDelta().y();
  float dz = box.getDelta().z();

  if (axis == 0) {
    plane.addTriangle(RTTriangle(
      Vector(pos, y, z), 
      Vector(pos, y+dy, z), 
      Vector(pos, y+dy, z+dz)
    ));
    plane.addTriangle(RTTriangle(
      Vector(pos, y, z), 
      Vector(pos, y, z+dz), 
      Vector(pos, y+dy, z+dz)
    ));
  } else if (axis == 1) {
    plane.addTriangle(RTTriangle(
      Vector(x, pos, z), 
      Vector(x, pos, z+dz), 
      Vector(x+dx, pos, z+dz)
    ));
    plane.addTriangle(RTTriangle(
      Vector(x, pos, z),
      Vector(x+dx, pos, z),
      Vector(x+dx, pos, z+dz)
    ));
  } else {
    plane.addTriangle(RTTriangle(
      Vector(x, y, pos), 
      Vector(x, y+dy, pos), 
      Vector(x+dx, y+dy, pos)
    ));
    plane.addTriangle(RTTriangle(
      Vector(x, y, pos),
      Vector(x+dx, y, pos),
      Vector(x+dx, y+dy, pos)
    ));
  }

  return plane;

}
