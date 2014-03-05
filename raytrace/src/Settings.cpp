#include "Settings.h"

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

int Settings::width() const {
  return this->_width;
}

int Settings::height() const {
  return this->_height;
}

int Settings::numSamples() const {
  return this->_numSamplesPerPixel;
}

char * Settings::input() const {
  return _input;
}

char * Settings::output() const {
  return _output;
}

void Settings::print() const {

  printf("Settings: \n");
  printf("\tWidth: %d\n", width());
  printf("\tHeight: %d\n", height());
  printf("\tNum Samples Per Pixel: %d\n", numSamples());
  printf("\tReading: %s\n", input());
  printf("\tWriting: %s\n", output());
}
