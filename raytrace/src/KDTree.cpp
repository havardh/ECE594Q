#include "KDTree.h"

KDTree::~KDTree() {
  if (leftChild) delete leftChild;
  if (rightChild) delete rightChild;  
}


void KDTree::build(vector<RTShape*> shapes, int depth) {

  this->axis  = depth % 3;
  this->depth = depth;
  this->median = findMedian(shapes, axis);

  if (terminate(shapes.size())) { 

    setShapes(shapes);

  } else {

    BoundingBoxes boxes = getBoundingBox().split(this->median, this->axis);
    KDTree *left = new KDTree();
    KDTree *right = new KDTree();

    left->setBoundingBox(boxes.first);
    left->setTerminationCondition(getTerminationCondition());
    right->setBoundingBox(boxes.second);
    right->setTerminationCondition(getTerminationCondition());
    
    left->build(left->filter(shapes), depth+1);
    right->build(right->filter(shapes), depth+1);

    setLeft(left);
    setRight(right);
  }

}

bool KDTree::terminate(int numShapes) {

  if (numShapes <= terminationCondition) {
    return true;
  } else {
    return false;
  }
}

void KDTree::setTerminationCondition(int condition) {
  terminationCondition = condition;
}

float KDTree::findMedian(vector<RTShape*> shapes, int axis) {
  vector<RTShape*>::iterator it;

  float m = 0;
  for (it = shapes.begin(); it != shapes.end(); ++it) {
    m += (*it)->getPosition().get(axis);
  }

  return m;
}

vector<RTShape*> KDTree::filter(vector<RTShape*> shapes) {
  
  vector<RTShape*> result;

  vector<RTShape*>::iterator it;
  for (it = shapes.begin(); it != shapes.end(); ++it) {

    RTShape *shape = *it;
    BoundingBox shapeBox = shape->getBoundingBox();
    
    if (shapeBox.intersects(box)) {
      result.push_back(shape);
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

KDTree* KDTree::getLeft() {
  return leftChild;
}

KDTree* KDTree::getRight() {
  return rightChild;
}

bool KDTree::isChild() {
  return !leftChild && !rightChild;
}

int KDTree::size() {
  return shapes.size();
}
