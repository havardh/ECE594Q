#include "ZBuffer.h"

bool sortByZIndex(Sample &first, Sample &second) {
  return first.z < second.z;
}

void ZBuffer::add(Sample sample) {
  samples.push_back(sample);
  samples.sort(sortByZIndex);
}

Sample ZBuffer::get() {

  if (opacityOneReturned) {
    Sample s = { -1, -1, { 0,0,0 } };
    return s;
  }

  Sample s = samples.front();
  samples.pop_front();
  
  if (s.opacity == 1) {
    opacityOneReturned = true;
  }
  
  return s;
}

std::vector<Sample> ZBuffer::getSamples() {
  std::vector<Sample> S;

  while(samples.size()) {
    S.push_back(samples.front());
    samples.pop_front();
  }

  return S;
}

Color ZBuffer::getColor() {

  Color color = { 0,0,0 };

  std::vector<Sample> S = getSamples();

  std::vector<Sample>::reverse_iterator it;
  for (it = S.rbegin(); it != S.rend(); ++it) {
    
    color.red = (uint8_t)(it->color.red * it->opacity) + (uint8_t)(color.red * (1-it->opacity));
    color.green = (uint8_t)(it->color.green * it->opacity) + (uint8_t)(color.green * (1-it->opacity));
    color.blue = (uint8_t)(it->color.blue * it->opacity) + (uint8_t)(color.blue * (1-it->opacity));
  }

  return color;

}
