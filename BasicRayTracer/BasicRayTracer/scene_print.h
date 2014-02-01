#ifndef _SCENE_PRINT_H_
#define _SCENE_PRINT_H_

#include "scene_io.h"

void print_scene(SceneIO*);
void print_camera(CameraIO*);

void print_light(LightIO*);
void print_lights(LightIO*);

void print_object(ObjIO*);
void print_objects(ObjIO*);

void print_materials(MaterialIO*, int);
void print_material(MaterialIO*);

void print_sphere(SphereIO*);
void print_polyset(PolySetIO*);
void print_polygons(PolygonIO*, int);
void print_polygon(PolygonIO*);

void print_vertices(VertexIO*, int);
void print_vertex(VertexIO*);

#endif /* _SCENE_PRINT_H_ */
