#ifndef _TIMEBENCHMARK_H_
#define _TIMEBENCHMARK_H_

#include "StopWatch.h"
#include <vector>

using std::vector;

class Action {
public:
  virtual void execute() = 0;
  virtual const char* describe() = 0;
  virtual void setup() {}
};

class TimeBenchmark {

public:
  void setNumberOfExecutions(int);
  void setStopWatch(StopWatch*);
  void addAction(Action*);
  void run();

  void print();

private:
  int _numberOfExecutions = 1;
  vector<Action*> _actions;
  StopWatch *_stopWatch;

};

#endif /* _TIMEBENCHMARK_H_ */
