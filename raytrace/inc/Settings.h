#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#define SETTINGS_DEFAULT_WIDTH 100
#define SETTINGS_DEFAULT_HEIGHT 100
#define SETTINGS_DEFAULT_VALIAS 1
#define SETTINGS_DEFAULT_HALIAS 1
#define SETTINGS_DEFAULT_NUM_SAMPLES 10
#define SETTINGS_DEFAULT_USE_THREADS false
#define SETTINGS_DEFAULT_INPUT "input.ascii"
#define SETTINGS_DEFAULT_OUTPUT "output.png"
#define SETTINGS_DEFAULT_ENV_MAP 0
#define SETTINGS_DEFAULT_NUM_THREADS_N 2
#define SETTINGS_DEFAULT_NUM_THREADS_M 2

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

class Settings {
 
public:
  
  Settings() :
    _width(SETTINGS_DEFAULT_WIDTH),
    _height(SETTINGS_DEFAULT_HEIGHT),
    _valias(SETTINGS_DEFAULT_VALIAS),
    _halias(SETTINGS_DEFAULT_HALIAS),
    _useThreads(SETTINGS_DEFAULT_USE_THREADS),
    _numThreadsN(SETTINGS_DEFAULT_NUM_THREADS_N),
    _numThreadsM(SETTINGS_DEFAULT_NUM_THREADS_M),
    _numSamplesPerPixel(SETTINGS_DEFAULT_NUM_SAMPLES),
    _environmentMap(SETTINGS_DEFAULT_ENV_MAP),
    _input(SETTINGS_DEFAULT_INPUT),
    _output(SETTINGS_DEFAULT_OUTPUT)
  {}

  void parse(int,char*[]);
  int width() const;
  int height() const;
  char *input() const;
  char *output() const;
  int valias() const;
  int halias() const;
  int numSamples() const;

  bool useThreads() const;
  int numThreadsN() const;
  int numThreadsM() const;

  char * environmentMap() const; 

  void print() const;
  
private:
  void parseResolution(char *);
  void parseNumSamples(char *);
  void parseOutput(char *);
  void parseInput(char *);
  void parseAlias(char*);
  void parseNumThreads(char *);
  void parseEnvironmentMap(char *);
  int _width, _height, _numSamplesPerPixel, _valias, _halias;
  char *_input, *_output, *_environmentMap;
  bool _useThreads;
  int _numThreadsN, _numThreadsM;
 
};

extern Settings settings;


#endif /* _SETTINGS_H_ */
 
