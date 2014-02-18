#ifndef _SPHERETESTHELPER_H_
#define _SPHERETESTHELPER_H_


#define CHECK_INTERSECTS_AT(s, ray, px, py, pz)        \
  {                                                 \
    IntersectionPtr I = s.intersect(ray);           \
    CHECK( I != nullptr );                          \
    DOUBLES_EQUAL(px, I->getPoint().x(), 0.0001); \
    DOUBLES_EQUAL(py, I->getPoint().y(), 0.0001); \
    DOUBLES_EQUAL(pz, I->getPoint().z(), 0.0001); \
  }

#define CHECK_NORMAL_AT(s, point, px, py, pz)  \
  {                                                 \
    VectorPtr I = s.normal(point);                  \
    CHECK( I != nullptr );                          \
    DOUBLES_EQUAL(px, I->x(), 0.0001);            \
    DOUBLES_EQUAL(py, I->y(), 0.0001);            \
    DOUBLES_EQUAL(pz, I->z(), 0.0001);            \
  }


#endif /* _SPHERETESTHELPER_H_ */
