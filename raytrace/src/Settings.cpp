#include "Settings.h"
#include "Dbg.h"

Settings settings;


void Settings::parse(int argc, char *argv[]) {
  for (int i=0; i<argc; i++) {
    char * parameter = argv[i];

    char option = parameter[1];
    char *arg = &parameter[2];
    switch (option) {

    case 'r': parseResolution(arg); break;
    case 'n': parseNumSamples(arg); break;
    case 'i': parseInput(arg);      break;
    case 'o': parseOutput(arg);     break;
    case 'a': parseAlias(arg);      break;
    case 't': parseNumThreads(arg); break;
    case 'e': parseEnvironmentMap(arg); break;
    case 'p': _progress = true;  break;

    }
  }
}

void Settings::parseResolution(char *res) {
  char param[10];
  strcpy(param, res);
  char * split = strchr(param, ':');

  (*split++) = '\0';

  this->_width = atoi(param);
  this->_height = atoi(split);
}

void Settings::parseNumSamples(char *res) {
  this->_numSamplesPerPixel = atoi(res);
}

void Settings::parseOutput(char *output) {
  _output = output;
}

void Settings::parseInput(char *input) {
  _input = input;
}

void Settings::parseAlias(char*arg) {
  char param[10];
  strcpy(param, arg);
  char * split = strchr(param, ':');

  (*split++) = '\0';

  this->_valias = atoi(param);
  this->_halias = atoi(split);

}

void Settings::parseNumThreads(char *res) {
  char param[10];
  strcpy(param, res);
  char * split = strchr(param, ':');

  (*split++) = '\0';

  this->_useThreads = true;
  this->_numThreadsN = atoi(param);
  this->_numThreadsM = atoi(split);
}

void Settings::parseEnvironmentMap(char *map) {
  _environmentMap = map;
}

void Settings::reset() {
  _width = SETTINGS_DEFAULT_WIDTH;
  _height = SETTINGS_DEFAULT_HEIGHT;
  _valias = SETTINGS_DEFAULT_VALIAS;
  _halias = SETTINGS_DEFAULT_HALIAS;
  _useThreads = SETTINGS_DEFAULT_USE_THREADS;
  _numThreadsN = SETTINGS_DEFAULT_NUM_THREADS_N;
  _numThreadsM = SETTINGS_DEFAULT_NUM_THREADS_M;
  _numSamplesPerPixel = SETTINGS_DEFAULT_NUM_SAMPLES;
  _progress = SETTINGS_DEFAULT_PROGRESS;
  _environmentMap = SETTINGS_DEFAULT_ENV_MAP;
  _input = SETTINGS_DEFAULT_INPUT;
  _output = SETTINGS_DEFAULT_OUTPUT;
}

int Settings::width() const {
  return this->_width;
}

int Settings::height() const {
  return this->_height;
}

int Settings::valias() const {
  return _valias;
}

int Settings::halias() const {
  return _halias;
}

int Settings::numSamples() const {
  return this->_numSamplesPerPixel;
}

bool Settings::progress() const {
  return this->_progress;
}

bool Settings::useThreads() const {
  return _useThreads;
}

int Settings::numThreadsN() const {
  return _numThreadsN;
}

int Settings::numThreadsM() const {
  return _numThreadsM;
}

char * Settings::input() const {
  return _input;
}

char * Settings::output() const {
  return _output;
}

char * Settings::environmentMap() const { 
  return _environmentMap; 
}

void Settings::print() const {

  printf("Settings: \n");
  printf("\tWidth: %d\n", width());
  printf("\tHeight: %d\n", height());
  printf("\tVertical Antialiasing: %d\n", valias());
  printf("\tHorizontal Antialiasing: %d\n", halias());
  printf("\tNum Samples Per Pixel: %d\n", numSamples());
  printf("\tReading: %s\n", input());
  printf("\tWriting: %s\n", output());
  if (useThreads()) {
    printf("\tRunning with Threads (%dx%d)\n", numThreadsN(), numThreadsM());
  }
  
}
