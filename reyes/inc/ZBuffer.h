#ifndef _ZBUFFER_H_
#define _ZBUFFER_H_

#include "Color.h"
#include <list>
#include <vector>

typedef struct {
  float z;
  float opacity;
  Color color;
} Sample;

class ZBuffer {

private:
  std::list<Sample> samples;
  bool opacityOneReturned;

  std::vector<Sample> getSamples();

public:
  ZBuffer() { opacityOneReturned = false; }
  void add(Sample sample);
  Sample get();
  Color getColor();

};

#endif /* _ZBUFFER_H_ */
