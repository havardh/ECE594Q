#ifndef _RTSHAPE_H_
#define _RTSHAPE_H_

#include "Ray.h"
#include "RTMaterial.h"
#include <vector>

class RTShape {
  
public:
  virtual ~RTShape() {}
  virtual bool intersect(const Ray &) = 0;

  void addMaterial(RTMaterial);
  int getMaterialCount() const;
  const RTMaterial getMaterial(int) const;

private:
  std::vector<RTMaterial> materials;
  

};

#endif /* _RTSHAPE_H_ */
