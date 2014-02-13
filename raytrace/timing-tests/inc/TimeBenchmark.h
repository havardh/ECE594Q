#ifndef _TIMEBENCHMARK_H_
#define _TIMEBENCHMARK_H_

#include "Timer.h"
#include <vector>

using std::vector;

class Action {
public:
  void execute();
};

class TimeBenchmark {

public:
  virtual void run() = 0;

  void setTimer(Timer *);

  void start(const char*);
  void lap(const char*);
  void stop();

  ull_t getStart();
  ull_t getLap(int); 
  ull_t getStop(); 

  int numLaps();
  ull_t totalDuration();
  ull_t lapTime(int);

  void print();

private:
  Timer *_timer;

  vector<ull_t> times;

};

#endif /* _TIMEBENCHMARK_H_ */
