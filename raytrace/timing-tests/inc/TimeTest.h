#ifndef _TIMETEST_H_
#define _TIMETEST_H_

class TimeTest {

public:
  virtual void run() = 0;
  void start(const char*);
  void lap(const char*);
  void stop();
  
  

};

#endif /* _TIMETEST_H_ */
