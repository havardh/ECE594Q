#ifndef _SPHERETESTHELPER_H_
#define _SPHERETESTHELPER_H_


#define CHECK_INTERSECTS_AT(s, ray, x, y, z)        \
  {                                                 \
    IntersectionPtr I = s.intersect(ray);           \
    CHECK( I != nullptr );                          \
    DOUBLES_EQUAL(x, I->getPoint().get(0), 0.0001); \
    DOUBLES_EQUAL(y, I->getPoint().get(1), 0.0001); \
    DOUBLES_EQUAL(z, I->getPoint().get(2), 0.0001); \
  }

#define CHECK_NORMAL_AT(s, point, x, y, z)  \
  {                                                 \
    VectorPtr I = s.normal(point);                  \
    CHECK( I != nullptr );                          \
    DOUBLES_EQUAL(x, I->get(0), 0.0001);            \
    DOUBLES_EQUAL(y, I->get(1), 0.0001);            \
    DOUBLES_EQUAL(z, I->get(2), 0.0001);            \
  }


#endif /* _SPHERETESTHELPER_H_ */
