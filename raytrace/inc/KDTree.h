#ifndef _KDTREE_H_
#define _KDTREE_H_

#include <vector>
#include "RTShape.h"
#include "RTPolySet.h"
#include "Class.h"
#include "BBox.h"

using std::vector;

class KDTree {

public:

  ~KDTree();

  void build(vector<RTShape*>, int);

  bool terminate(vector<RTShape*>);
  float findMedian(vector<RTShape*>, int);

  vector<RTShape*> filter(vector<RTShape*>);

  bool isChild();
  int size();

  bool containsComposite(vector<RTShape*>);

  void setTerminationCondition(int);
  void setBoundingBox(BoundingBox);
  void setShapes(vector<RTShape*>);
  void setLeft(KDTree*);
  void setRight(KDTree*);

  int getTerminationCondition() const;
  BoundingBox getBoundingBox() const;
  KDTree* getLeft();
  KDTree* getRight();
  
private: 
  int axis;
  int depth;
  float median;
  int terminationCondition = 1;

  BoundingBox box;
  vector<RTShape*> shapes;

  KDTree *leftChild = 0;
  KDTree *rightChild = 0;

};


#endif /* _KDTREE_H_ */
