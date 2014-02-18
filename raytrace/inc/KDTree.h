#ifndef _KDTREE_H_
#define _KDTREE_H_

#include <vector>
#include "RTShape.h"
#include "RTSphere.h"
#include "RTPolySet.h"
#include "RTShapeFactory.h"
#include "Class.h"
#include "BBox.h"
#include "Dbg.h"
using std::vector;

class KDTree {

public:

  ~KDTree();

  void build(vector<RTShape*>, int);
  IntersectionPtr intersect(const Ray&) const;

  bool terminate(vector<RTShape*>) const;
  float findMedian(vector<RTShape*>, int) const;

  vector<RTShape*> filter(vector<RTShape*>) const;

  bool isChild() const;
  int size() const;

  bool containsComposite(vector<RTShape*>) const;

  void setTerminationCondition(int);
  void setBoundingBox(BoundingBox);
  void setShapes(vector<RTShape*>);
  void setLeft(KDTree*);
  void setRight(KDTree*);

  int getTerminationCondition() const;
  BoundingBox getBoundingBox() const;
  KDTree* getLeft() const;
  KDTree* getRight() const;

  void print() const;

  int numNodes() const;
  int numChildren() const;
  int height() const;
  int numShapeRefs() const;

  bool isLeftOfPlane(RTPolySet, Ray);

private: 
  int axis;
  int depth;
  float median;
  int terminationCondition = 1;

  BoundingBox box;
  vector<RTShape*> shapes;

  KDTree *leftChild = 0;
  KDTree *rightChild = 0;

  IntersectionPtr intersectChildNode(const Ray &ray) const;
  std::vector<IntersectionPtr> intersectionsChildNode(const Ray ray) const;
};


#endif /* _KDTREE_H_ */
