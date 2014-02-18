#include "KDTree.h"

KDTree::~KDTree() {
  if (leftChild) delete leftChild;
  if (rightChild) delete rightChild;  
}


void KDTree::build(vector<RTShape*> shapes, int depth) {

  this->axis  = depth % 3;
  this->depth = depth;
  this->median = findMedian(shapes, axis);

  DPRINTF("%d %d\n", depth, shapes.size());
  if (terminate(shapes)) {
    setShapes(shapes);
  } else {
    BoundingBoxes boxes = getBoundingBox().split(this->median, this->axis);

    KDTree *left = new KDTree();
    left->setBoundingBox(boxes.first);
    left->setTerminationCondition(getTerminationCondition());
    left->build(left->filter(shapes), depth+1);
    setLeft(left);

    KDTree *right = new KDTree();
    right->setBoundingBox(boxes.second);
    right->setTerminationCondition(getTerminationCondition());
    right->build(right->filter(shapes), depth+1);
    setRight(right);
  }

}

IntersectionPtr KDTree::intersect(const Ray &ray) const {
  if (isChild()) {
    return intersectChildNode(ray);
  } else {

    RTPlane plane = RTShapeFactory::createPlane(getBoundingBox(), axis, median);

    KDTree *first, *last;
    if (plane.isToLeftOf(ray, axis)) {
      first = getLeft();
      last = getRight();
    } else {
      first = getRight();
      last = getLeft();
    }

    IntersectionPtr intersection = first->intersect(ray);
    if ( intersection != nullptr) {
      DPRINTF("Case 1\n");
      return intersection;
    }

    if (plane.intersect(ray)) {
      DPRINTF("Case 2\n");
      intersection = last->intersect(ray);
      if ( intersection != nullptr) {
        DPRINTF("Case 3\n");
        return intersection;
      }
    }

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
  
  std::vector<IntersectionPtr> intersections;
  vector<RTShape*>::const_iterator it;
  DPRINTF("Searching through %d\n", shapes.size());
  for(it = shapes.begin(); it != shapes.end(); ++it) {

    IntersectionPtr intersection = (*it)->intersect(ray);
     
    if (intersection != nullptr) {

      if (intersection->getShape()->shadeIntersection(*intersection)) {
        intersections.push_back(intersection);
      }
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

float KDTree::findMedian(vector<RTShape*> shapes, int axis) const {
  vector<RTShape*>::iterator it;

  float m = 0;
  for (it = shapes.begin(); it != shapes.end(); ++it) {
    m += (*it)->getBoundingBox().center().get(axis);
  }

  return m / shapes.size();
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

void KDTree::print() const {

  printf("Depth: %d\n", depth);
  printf("Median: %f\n", median);
  printf("Num shapes: %lu\n", shapes.size());
  if (!isChild()) {
    getLeft()->print();
    getRight()->print();
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
