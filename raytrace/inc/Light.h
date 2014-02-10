#ifndef _LIGHT_H_ 
#define _LIGHT_H_

#include "Matrix.h"
#include "RTColor.h"
#include <vector>

enum RTLightType {
  POINT, DIRECTIONAL, SPOT
};

class Light {

public:
  
  Light(RTLightType type, Matrix pos, Matrix dir, RTColor color, float dropOffRate, float cutOffAngle) {
    _type = type;
    _position = pos;
    _direction = dir;
    _color = color;
    _dropOffRate = dropOffRate;
    _cutOffAngle = cutOffAngle;
  }
  
  Light(Matrix pos, Matrix dir, RTColor color, float dropOffRate, float cutOffAngle) {
    _type = POINT;
    _position = pos;
    _direction = dir;
    _color = color;
    _dropOffRate = dropOffRate;
    _cutOffAngle = cutOffAngle;
  }

  RTLightType getType() const { return _type; }
  const Matrix& getPosition() const { return _position; }
  const Matrix& getDirection() const { return _direction; }
  const RTColor& getColor() const { return _color; }
  float getDropOffRate() const { return _dropOffRate; }
  float getCutOffAngle() const { return _cutOffAngle; }

  const Matrix& getDirectionFrom(const Matrix p) const {
    if (getType() == POINT) {
      return getPosition() - p;
    } else {
      return getDirection() * -1;
    }
  }

  void setType(RTLightType type) {  _type = type; }
  void setPosition(const Matrix& position) {  _position = position; }
  void setDirection(const Matrix& direction) {  _direction = direction; }
  void setColor(const RTColor& color) {  _color = color; }
  void setDropOffRate(float dropOffRate) {  _dropOffRate = dropOffRate; }
  void setCutOffAngle(float cutOffAngle) {  _cutOffAngle = cutOffAngle; }

private:
  RTLightType _type;
  Matrix _position, _direction;
  RTColor _color;
  float _dropOffRate, _cutOffAngle;

};

typedef std::shared_ptr<Light> LightPtr;
typedef std::vector<Light>::const_iterator LightIter;

#endif /* _LIGHT_H_ */
