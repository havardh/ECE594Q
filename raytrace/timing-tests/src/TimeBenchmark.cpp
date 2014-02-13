#include "TimeBenchmark.h"

void TimeBenchmark::setNumberOfExecutions(int i) {
  _numberOfExecutions = i;
}

void TimeBenchmark::setStopWatch(StopWatch *stopWatch) {
  _stopWatch = stopWatch;
}

void TimeBenchmark::run() {

  vector<Action*>::iterator it;
  for (it = _actions.begin(); it != _actions.end(); ++it) {
    (*it)->setup();
  }

  _stopWatch->start("");


  for (it = _actions.begin(); it != _actions.end(); ++it) {


    for (int i=0; i<_numberOfExecutions; i++) {
      (*it)->execute();
    }

    _stopWatch->lap((*it)->describe());
  }

  _stopWatch->stop();
}

void TimeBenchmark::addAction(Action *action) {
  _actions.push_back(action);
}

void TimeBenchmark::print() {
  printf("----------------------\n");
  printf("Running Benchmark: <name>\n");
  printf("Start: %llu\n", _stopWatch->getStart());
  printf("End: %llu\n", _stopWatch->getStop());
  printf("Total Duration: %llu\n", _stopWatch->totalDuration());
  printf("Laps recorded: %d\n", _stopWatch->numLaps());
  printf("----------------------\n\n");
  for (int i=0; i<_stopWatch->numLaps(); i++) {
    printf("----------------------\n");
    printf("Lap: %s\n", _stopWatch->lapName(i));
    
    printf("Duration %llu\n", _stopWatch->lapTime(i) / _numberOfExecutions);
  }
  printf("----------------------\n");
}
