#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

class ViewPort {

public:
  ViewPort(int width, int height) : _width(width), _height(height) {}

  int getWidth() { return _width; }
  int getHeight() { return _height; }

private:
  int _width;
  int _height;
}

#endif /* _VIEWPORT_H_ */
