#include "scene_print.h"

void print_scene(SceneIO *scene) {

  print_camera(scene->camera);
  print_lights(scene->lights);
  print_objects(scene->objects);

}

void print_vector(Vec & v) {
  printf("(%2.2f, %2.2f, %2.2f)\n", v[0], v[1], v[2]);
}

void print_point(Point &point) {
  print_vector(point);
}

void print_color(Color &color) {
  print_vector(color);
}

void print_camera(CameraIO *camera) {
  printf("CAMERA {\n");
  printf("\tPoisition: "); print_point(camera->position);
  printf("\tView Direction: "); print_vector(camera->viewDirection);
  printf("\tFocal Distance: %f\n", camera->focalDistance); 
  printf("\tOrtho Up: "); print_vector(camera->orthoUp);
  printf("\tVertical FOV: %f\n", camera->verticalFOV);
  printf("}\n");
}

const static char* LightTypeName[] = {
  "POINT_LIGHT","DIRECTIONAL_LIGHT","SPOT_LIGHT"
};
void print_light(LightIO *light) {
  printf("LIGHT {\n");
  printf("\tType: %s\n", LightTypeName[light->type]);
  printf("\tPoisition: "); print_point(light->position);
  printf("\tDirection: "); print_vector(light->direction);
  printf("\tColor: "); print_color(light->color);
  printf("\tDrop Off Rate: %f\n", light->dropOffRate);
  printf("\tCut Off Angle: %f\n", light->cutOffAngle);
  printf("}\n");
}

void print_lights(LightIO *light) {
  if (light) {
    print_light(light);
    print_lights(light->next);
  }
}

const static char* ObjTypeName[] = {
  "SPHERE_OBJ", "POLYSET_OBJ"
};
void print_object(ObjIO *object) {
  printf("OBJECT {\n");
  printf("\tName: %s\n", (object->name ? object->name : "No name"));
  printf("\tType: %s\n", ObjTypeName[object->type]);
  printf("\tNum Materials: %lu\n", object->numMaterials);
  print_materials(object->material, object->numMaterials);
  if (object->type == SPHERE_OBJ) {
    print_sphere((SphereIO*)object->data);
  } else if (object->type == POLYSET_OBJ) {
    print_polyset((PolySetIO*)object->data);
  }
  printf("}\n");
  
}

void print_objects(ObjIO *object) {
  if (object) {
    print_object(object);
    print_objects(object->next);
  }
}

void print_materials(MaterialIO *material, int n) {
  for (int i=0; i<n; i++) {
    print_material(&material[i]);
  }
}

void print_material(MaterialIO *material) {
  printf("\tMATERIAL {\n");
  printf("\t\tDiff Color: "); print_color(material->diffColor);
  printf("\t\tAmbient Color: "); print_color(material->ambColor);
  printf("\t\tAmbient Color: "); print_color(material->specColor);
  printf("\t\tAmbient Color: "); print_color(material->emissColor);
  printf("\t\tShininess: %f\n", material->shininess);
  printf("\t\tKtran: %f\n", material->ktran);
  printf("\t}\n");

}

void print_sphere(SphereIO *sphere) {

  printf("\tDATA {\n");
  printf("\t\tOrigin: "); print_point(sphere->origin);
  printf("\t\tRadius: %f\n", sphere->radius);
  printf("\t\tXAxis: "); print_vector(sphere->xaxis);
  printf("\t\tXLength: %f\n", sphere->xlength);
  printf("\t\tYAxis: "); print_vector(sphere->yaxis);
  printf("\t\tYLength: %f\n", sphere->ylength);
  printf("\t\tZAxis: "); print_vector(sphere->zaxis);
  printf("\t\tZLength: %f\n", sphere->zlength);
  printf("\t}\n");
  
}
static const char* PolySetName[] = {
  "POLYSET_TRI_MESH", "POLYSET_FACE_SET", "POLYSET_QUAD_MESH"
};
static const char* NormTypeName[] = {
  "PER_VERTEX_NORMAL", "PER_FACE_NORMAL"
};
static const char* MaterialBindingName[] = {
  "PER_OBJECT_MATERIAL", "PER_VERTEX_MATERIAL"
};
void print_polyset(PolySetIO *polyset) {
  printf("\tPOLYSET {\n");
  printf("\t\tType: %s\n", PolySetName[polyset->type]);
  printf("\t\tNormType: %s\n", NormTypeName[polyset->normType]);
  printf("\t\tMaterialBinding: %s\n", MaterialBindingName[polyset->materialBinding]);
  printf("\t\tHas Texture Coords: %d\n", polyset->hasTextureCoords);
  printf("\t\t(numPolys / rowSize) = (%lu / %lu)\n", polyset->numPolys, polyset->rowSize);
  print_polygons(polyset->poly, polyset->numPolys);
  printf("}\n");
}

void print_polygons(PolygonIO *polygons, int n) {
  for (int i=0; i<n; i++) {
    print_polygon(&polygons[i]);
  }
}

void print_polygon(PolygonIO *polygon) {
  printf("\t\tPOLYGON {\n");
  printf("\t\t\tNum Vertices: %lu\n", polygon->numVertices);
  printf("\t\t\tVERTICES {\n");
  print_vertices(polygon->vert, polygon->numVertices);
  printf("\t\t}\n");
}

void print_vertices(VertexIO *vertices, int n) {
  for(int i=0; i<n; i++) {
    print_vertex(&vertices[i]);
  }
}

void print_vertex(VertexIO *vertex) {
  printf("\t\t\t\tVERTEX {\n");
  printf("\t\t\t\t\tPos: "); print_point(vertex->pos);
  printf("\t\t\t\t\tNorm: "); print_vector(vertex->norm);
  printf("\t\t\t\t\tMaterial Index: %lu\n", vertex->materialIndex);
  printf("\t\t\t\t\t(s, t) = (%2.2f, %2.2f)\n", vertex->s, vertex->t);
  printf("\t\t\t\t}\n");
}
