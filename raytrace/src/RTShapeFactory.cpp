#include "RTShapeFactory.h"
#include "Dbg.h"

static ColorShaderRandom rShader;
static ColorShaderGradient gShader;
static ColorShaderCheckerboard cShader(10,10);
static ColorShaderTexture tShader("earth.jpg");
static ColorShaderIdentity iShader;

RTTriangle RTShapeFactory::createTriangle(PolygonIO *polygon) {

  return RTTriangle(
    Matrix(polygon->vert[0].pos), 
    Matrix(polygon->vert[1].pos), 
    Matrix(polygon->vert[2].pos)
  );
}

RTShape* RTShapeFactory::createShape(ObjIO *obj) {
  
  RTShape *shape = NULL;

  if (obj->type == SPHERE_OBJ) {

    SphereIO *io = (SphereIO*)obj->data;
    shape = new RTSphere(io->origin, io->radius);
    shape->setColorShader(&iShader);

  } else if (obj->type == POLYSET_OBJ) {

    RTPolySet *set = new RTPolySet();
    set->setColorShader(&iShader);
    PolySetIO *io = (PolySetIO*)obj->data;
    bool i = 0; // setting the is upper property for triangles
    for (int i=0; i<io->numPolys; i++) {
      RTTriangle t = RTShapeFactory::createTriangle(&io->poly[i]);
      t.setColorShader(&iShader);
      t.setIsUpper(i++ % 2 == 0);
      t.setParent(set);
      set->addTriangle(t);
    }
    set->calculateMidpoint();
    shape = set;

  }

  if (shape) {
    for (int i=0; i<obj->numMaterials; i++) {
      shape->addMaterial(RTShapeFactory::createMaterial(&obj->material[i]));
    }
  }

  return shape;
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
