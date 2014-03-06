#include "Scene.h"
#include "Dbg.h"

//#define USE_BBH
#define USE_KDTREE

Scene::~Scene() {
}

void Scene::setScene() {

#ifdef USE_BBH
  bbh.build(shapes);
#endif

#ifdef USE_KDTREE
  //DPRINTF("..\n");
  updateTree();
  //tree.print(true);
  //DPRINTF("..\n");
#endif
}

void Scene::updateTree() {
  SurfaceAreaHeuristic sah;
  tree.setHeuristic(&sah);
  tree.setBoundingBox(computeBoundingBox());
  tree.setTerminationCondition(333); // test1 = 60, test2 = 333,  
  tree.build(shapes, 0);
}

void Scene::add(const Light light) {
  lights.push_back(light);
}

void Scene::add(RTShape *shape) {
  shapes.push_back(shape);
}

IntersectionPtr Scene::intersect(const Ray ray) {
  //DPRINTF("\n");

#ifdef USE_BBH
  return bbh.intersect(ray);
#endif
  
#ifdef USE_KDTREE
  return tree.intersect(ray);
#else
  std::vector<IntersectionPtr> I = intersections(ray);

  IntersectionPtr intersection(NULL);
  std::vector<IntersectionPtr>::iterator it;
  for (it = I.begin(); it != I.end(); ++it) {
    if (intersection == nullptr || *(*it) < *intersection ) {
      //DPRINTF("\n");
      intersection = *it;
    }
  }

  return intersection;
#endif
}

std::vector<IntersectionPtr> Scene::intersections(const Ray ray) {
  
  RTShapeIter it;
  std::vector<IntersectionPtr> intersections;
  for(it = shapesBegin(); it != shapesEnd(); ++it) {

    IntersectionPtr intersection = (*it)->intersect(ray);
     
    if (intersection != nullptr) {

      if (intersection->getShape()->shadeIntersection(*intersection)) {
        intersections.push_back(intersection);
      }
    }
  }

  return intersections; 

}

BoundingBox Scene::computeBoundingBox() {

  BoundingBox box;

  std::vector<RTShape*>::iterator it;
  for (it = shapes.begin(); it != shapes.end(); ++it) {
    box = box.unionWith((*it)->getBoundingBox());
  }
  
  return box;
}
