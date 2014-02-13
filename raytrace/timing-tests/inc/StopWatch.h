#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

#include "Timer.h"
#include <vector>

using std::vector;


class StopWatch {

public:

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
  const char* lapName(int);

  void print();

private:
  Timer *_timer;

  vector<ull_t> times;
  vector<const char*> lapNames;

};

#endif /* _STOPWATCH_H_ */
