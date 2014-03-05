#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#define SETTINGS_DEFAULT_WIDTH 100
#define SETTINGS_DEFAULT_HEIGHT 100
#define SETTINGS_DEFAULT_NUM_SAMPLES 10
#define SETTINGS_DEFAULT_INPUT "input.ascii"
#define SETTINGS_DEFAULT_OUTPUT "output.png"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

class Settings {
 
public:
  
  Settings() :
    _width(SETTINGS_DEFAULT_WIDTH),
    _height(SETTINGS_DEFAULT_HEIGHT),
    _numSamplesPerPixel(SETTINGS_DEFAULT_NUM_SAMPLES),
    _input(SETTINGS_DEFAULT_INPUT),
    _output(SETTINGS_DEFAULT_OUTPUT)
 {}

  void parse(int,char*[]);
  int width() const;
  int height() const;
  char *input() const;
  char *output() const;
  int numSamples() const;

  void print() const;
  
private:
  void parseResolution(char *);
  void parseNumSamples(char *);
  void parseOutput(char *);
  void parseInput(char *);
  int _width, _height, _numSamplesPerPixel;
  char *_input, *_output;
 
};

extern Settings settings;


#endif /* _SETTINGS_H_ */
 
