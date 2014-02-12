#include "RTShapeFactory.h"
#include "Dbg.h"

static ColorShaderRandom rShader;
static ColorShaderGradient gShader;
static ColorShaderCheckerboard cShader(10,10);
static ColorShaderTexture tShader("earth.jpg");
static ColorShaderIdentity iShader;

RTTriangle RTShapeFactory::createTriangle(PolygonIO *polygon, bool hasNormals, bool hasMaterials, RTPolySet *parent) {

  RTTriangle triangle(
    Matrix(polygon->vert[0].pos), 
    Matrix(polygon->vert[1].pos), 
    Matrix(polygon->vert[2].pos)
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

    SphereIO *io = (SphereIO*)obj->data;
    shape = new RTSphere(io->origin, io->radius);
    addMaterials(shape, obj);
    shape->setColorShader(&iShader);

  } else if (obj->type == POLYSET_OBJ) {

    RTPolySet *set = new RTPolySet();
    addMaterials(set, obj);
    set->setColorShader(&iShader);
    PolySetIO *io = (PolySetIO*)obj->data;
    bool i = 0; // setting the is upper property for triangles
    for (int i=0; i<io->numPolys; i++) {
      RTTriangle t = RTShapeFactory::createTriangle(
        &io->poly[i],
        io->normType == PER_VERTEX_NORMAL,
        io->materialBinding == PER_VERTEX_MATERIAL,
        set
      );
      t.setColorShader(&iShader);
      t.setIsUpper(i++ % 2 == 0);
      set->addTriangle(t);
    }
    set->calculateMidpoint();
    shape = set;

  }

  if (shape) {

  }

  return shape;
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
