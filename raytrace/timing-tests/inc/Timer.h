#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;

typedef unsigned long long ull_t;

class Timer {

 public:
  
  virtual ull_t time() {
    time_point<high_resolution_clock> t = high_resolution_clock::now();
    nanoseconds nsecs = duration_cast<nanoseconds>(t.time_since_epoch());
    return nsecs.count();
  }

};

#endif /* _TIMER_H_ */
