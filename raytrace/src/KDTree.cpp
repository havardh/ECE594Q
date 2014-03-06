#include "KDTree.h"

//#define KDTREE_NAIVE
#define KDTREE_BOUNDINGBOXES

KDTree::~KDTree() {
  if (leftChild) delete leftChild;
  if (rightChild) delete rightChild;
  if (_implicitHeuristic) delete _splitHeuristic;
}


void KDTree::build(vector<RTShape*> shapes, int depth) {

  this->axis  = depth % 3;
  this->depth = depth;
  this->median = getHeuristic()->findMedian(
    getBoundingBox(), shapes, axis);

  //DPRINTF("%d %d %d\n", depth, axis, shapes.size());
  if (terminate(shapes)) {
    setShapes(shapes);
  } else {
    BoundingBoxes boxes = getBoundingBox().split(this->median, this->axis);

    KDTree *left = new KDTree();
    left->setBoundingBox(boxes.first);
    left->setTerminationCondition(getTerminationCondition());
    left->setHeuristic(getHeuristic());
    left->build(left->filter(shapes), depth+1);
    setLeft(left);

    KDTree *right = new KDTree();
    right->setBoundingBox(boxes.second);
    right->setTerminationCondition(getTerminationCondition());
    right->setHeuristic(getHeuristic());
    right->build(right->filter(shapes), depth+1);
    setRight(right);
  }

  //print();

}

IntersectionPtr KDTree::intersect(const Ray &ray) const {
  if (isChild()) {
    //DPRINTF("child\n");
    return intersectChildNode(ray);
  } else {

#ifdef KDTREE_NAIVE

    IntersectionPtr intersection = getRight()->intersect(ray);
    if (intersection == nullptr) {
      return getLeft()->intersect(ray);
    } else {
      return intersection;
    }

#elif defined KDTREE_BOUNDINGBOXES
    
    float t_enter, t_exit;
    bool intersects = getBoundingBox().intersects(ray, t_enter, t_exit);

    if (!intersects) 
      return IntersectionPtr(NULL);
    
    float t = (median - ray.getOrigin().get(axis)) / ray.getDirection().get(axis);

    KDTree *near, *far;
    if (median > ray.getOrigin().get(axis)) {
      near = getLeft(); far = getRight();
    } else {
      near = getRight(); far = getLeft();
    }
    
    if (t >= t_exit || t < 0) {
      //DPRINTF("near\n");
      return near->intersect(ray);
    } else if (t <= t_enter) {
      //DPRINTF("far\n");
      return far->intersect(ray);
    } else {
      //DPRINTF("near\n");
      IntersectionPtr intersection = near->intersect(ray);
      if (intersection != nullptr) {
        //DPRINTF("far\n");
        IntersectionPtr farIntersection = far->intersect(ray);

        if (farIntersection != nullptr && (*farIntersection < *intersection)) {
          return farIntersection;
        } else {
          return intersection;
        }
      } else {
        //DPRINTF("far\n");
        return far->intersect(ray);
      }
    }


#else    

    RTPlane plane = RTShapeFactory::createPlane(getBoundingBox(), axis, median);
    KDTree *first, *last;
    if (plane.isToLeftOf(ray, axis)) {
      //DPRINTF("left\n");
      first = getLeft();
      last = getRight();
    } else {
      //DPRINTF("right\n");
      first = getRight();
      last = getLeft();
    }

    IntersectionPtr intersection = first->intersect(ray);
    if ( intersection != nullptr) {
      //DPRINTF("Case 1\n");
      return intersection;
    }

    if (plane.intersect(ray)) {
      //DPRINTF("intersecting\n");
      //DPRINTF("Case 2\n");
      intersection = last->intersect(ray);
      if ( intersection != nullptr) {
        //DPRINTF("Case 3\n");
        return intersection;
      }
    }
#endif
  }
  return IntersectionPtr(NULL);
}

IntersectionPtr KDTree::intersectChildNode(const Ray &ray) const {
  std::vector<IntersectionPtr> I = intersectionsChildNode(ray);

  IntersectionPtr intersection(NULL);
  std::vector<IntersectionPtr>::iterator it;
  for (it = I.begin(); it != I.end(); ++it) {
    if (intersection == nullptr || *(*it) < *intersection ) {
      intersection = *it;
    }
  }
  return intersection;
}

std::vector<IntersectionPtr> KDTree::intersectionsChildNode(const Ray ray) const {
  static int i=0;
  static int j=0;
  std::vector<IntersectionPtr> intersections;
  vector<RTShape*>::const_iterator it;
  //DPRINTF("Searching through %d\n", shapes.size());
  for(it = shapes.begin(); it != shapes.end(); ++it) {
    
    IntersectionPtr intersection = (*it)->intersect(ray);
     
    if (intersection != nullptr) {

      if (intersection->getShape()->shadeIntersection(*intersection)) {
        intersections.push_back(intersection);
      }
      //DPRINTF("Intersect: %d\n", i++);
    } else {
      //DPRINTF("Not Intersect: %d\n", j++);
    }
  }

  return intersections; 

}

bool KDTree::terminate(vector<RTShape*> shapes) const {

  int numShapes = shapes.size();

  if (numShapes <= terminationCondition && !containsComposite(shapes)) {
    return true;
  } else {
    return false;
  }
}

void KDTree::setTerminationCondition(int condition) {
  terminationCondition = condition;
}

vector<RTShape*> KDTree::filter(vector<RTShape*> shapes) const {
  
  vector<RTShape*> result;

  vector<RTShape*>::iterator it;
  for (it = shapes.begin(); it != shapes.end(); ++it) {

    RTShape *shape = *it;
    BoundingBox shapeBox = shape->getBoundingBox();

    if (shapeBox.intersects(box)) {

      if (shape->getID() == RTPolySet::shapeID ) {
        RTPolySet *set = (RTPolySet*) shape;

        for (int i=0; i<set->size(); i++) {
          RTTriangle *triangle = set->getTrianglePointer(i);
          BoundingBox triangleBox = triangle->getBoundingBox();
          if (triangleBox.intersects(box)) {
            result.push_back(triangle);
          }
        }
        
      } else {
        result.push_back(shape);
      }
    }
  }

  return result;
}

void KDTree::setHeuristic(SplitHeuristic *heuristic) {
  _splitHeuristic = heuristic;
}

void KDTree::setBoundingBox(BoundingBox b) {
  box = b;
}

void KDTree::setShapes(vector<RTShape*> shapes) {
  this->shapes = shapes;
}

void KDTree::setLeft(KDTree *tree) {
  leftChild = tree;
}

void KDTree::setRight(KDTree *tree) {
  rightChild = tree;
}

SplitHeuristic* KDTree::getHeuristic() {
  if (this->_splitHeuristic == 0) {
    this->_implicitHeuristic = true;
    this->_splitHeuristic = new MeanHeuristic();
  }

  return this->_splitHeuristic;
}

int KDTree::getTerminationCondition() const {
  return terminationCondition;
}

BoundingBox KDTree::getBoundingBox() const {
  return box;
}

KDTree* KDTree::getLeft() const {
  return leftChild;
}

KDTree* KDTree::getRight() const {
  return rightChild;
}

bool KDTree::isChild() const {
  return !leftChild && !rightChild;
}

int KDTree::size() const {
  return shapes.size();
}

bool KDTree::containsComposite(vector<RTShape*> shapes) const {

  vector<RTShape*>::iterator it;
  for (it = shapes.begin(); it != shapes.end(); ++it) {
    if ((*it)->getID() == RTPolySet::shapeID) {
      return true;
    }
  }
  return false;
}

void KDTree::print(bool recursive) const {

  printf("Depth: %d\n", depth);
  printf("Median: %f\n", median);
  printf("Num shapes: %lu\n", shapes.size());
  printf("Height: %d\n", height());
  printf("ShapeRefs: %d\n", numShapeRefs());
  printf("Num nodes: %d\n", numNodes());
  printf("Num children: %d\n", numChildren());
  printf("BoundingBox:\n");
  getBoundingBox().print();
  if (recursive && !isChild()) {
    getLeft()->print(recursive);
    getRight()->print(recursive);
  }

}

int KDTree::numNodes() const {

  if (isChild()) {
    return 1;
  } else {
    return 1 + getLeft()->numNodes() + getRight()->numNodes();
  }

}

int KDTree::numChildren() const {
  if (isChild()) {
    return 1;
  } else {
    return getLeft()->numChildren() + getRight()->numChildren();
  }
}

int KDTree::height() const {
  if (isChild()) {
    return 1;
  } else {
    int l = getLeft()->height();
    int r = getRight()->height();
    return l > r ? l+1 : r+1;
  }
}

int KDTree::numShapeRefs() const {
  if (isChild()) {
    return shapes.size(); 
  } else {
    return getLeft()->numShapeRefs() + getRight()->numShapeRefs();
  } 
}
