#ifndef _COLORTESTHELPER_H_
#define _COLORTESTHELPER_H_

#define COLOR_EQUAL(r,g,b, color) \
  CHECK_EQUAL(r, color.getRGBRed()) \
  CHECK_EQUAL(g, color.getRGBGreen()) \
  CHECK_EQUAL(b, color.getRGBBlue()) 

#define COLOR_EQUALS(expected, actual)           \
  COLOR_EQUAL(expected.getRGBRed(),             \
    expected.getRGBGreen(),                     \
    expected.getRGBBlue(),                      \
                actual)

#endif /* _COLORTESTHELPER_H_ */
