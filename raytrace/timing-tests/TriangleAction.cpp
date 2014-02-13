#ifndef _TRIANGLEACTION_H_
#define _TRIANGLEACTION_H_

#include "RTTriangle.h"
#include "TimeBenchmark.h"

class TriangleIntersectionAction : public Action {

public:

  virtual const char* describe() {
    return "Triangle Intersection";
  }

  virtual void setup() {
    triangle = RTTriangle(
      Matrix(1,1,20), 
      Matrix(2,1,40), 
      Matrix(2,2,10)
    );

    ray = Ray(Matrix(1,1,0), Matrix(0,0,1));

  }

  virtual void execute() {

    triangle.intersect(ray);

  }

private:
  RTTriangle triangle;
  Ray ray;

};

int main(void) {
  Timer timer;
  StopWatch watch;
  watch.setTimer(&timer);
  TimeBenchmark benchmark;
  benchmark.setStopWatch(&watch);
  benchmark.setNumberOfExecutions(1000000);

  TriangleIntersectionAction tia;
  benchmark.addAction(&tia);
  
  benchmark.run();
  benchmark.print();

  return 0;
}


#endif /* _TRIANGLEACTION_H_ */
