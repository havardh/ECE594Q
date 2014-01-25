#include "Mesh.h"


Mesh::Mesh(int m, int n) : _m(m), _n(n) {


  for (int i=0; i<_m *_n; i++) {
    float u = (float)(i / _n);
    float v = (float)(i % _n);

    Color c = { 255, 255, 255 };
    MeshPoint p = { Matrix(4,1), u / _m, v/_n, NULL, c };
    this->mesh.push_back(p);
  }

}

Matrix & Mesh::getPoint(int i) {
  return this->mesh[(size_t)i].point;
}

Matrix & Mesh::getPoint(int u, int v) {
  return getPoint( u * _n + v );
}

MeshPoint & Mesh::getMeshPoint(int u, int v) {
  return this->mesh[(size_t)(u*_n+v)];
}

Mesh & Mesh::projectOnto(Matrix &projectionMatrix) {

  for (int i=0; i<_m*_n; i++) {
    getPoint(i) = projectionMatrix * getPoint(i);
  }

  return *this;
  
}

Mesh & Mesh::transform(Matrix &transformMatrix) {

  for (int i=0; i<_m*_n; i++) {
    getPoint(i) = transformMatrix * getPoint(i);
  }

  return * this;
}


Mesh & Mesh::homogenize() {
  
  for (int i=0; i<_m*_n; i++) {
    getPoint(i).homogenize();
  }

  return *this;

}

BoundingBox Mesh::getBoundingBox() {

  float minx = getPoint(0).get(0,0);
  float miny = getPoint(0).get(1,0);
  float maxx = getPoint(0).get(0,0);
  float maxy = getPoint(0).get(1,0);
  
  for (int i=1; i<_m*_n; i++) {
    float x = getPoint(i).get(0,0);
    float y = getPoint(i).get(1,0);

    if ( x > maxx )
      maxx = x;

    if ( y > maxy )
      maxy = y;

    if ( x < minx )
      minx = x;

    if ( y < miny )
      miny = y;
  }
  
  return BoundingBox(minx, miny, maxx-minx, maxy-miny);
  
}

void Mesh::generateSurfaceNormals() {
  /*
  for (int i=0; i<_m; i++) {
    for (int j=0; j<_n; j++) {
      MeshPoint *p = &getMeshPoint(i,j);
      Matrix *n1 = &getMeshPoint(i, (j+1)%_n).point;
      Matrix *n2 = &getMeshPoint((i+1)%_m, (j+1)%_n).point;
      Matrix m1(
        n1->get(0) - p->point.get(0),
        n1->get(1) - p->point.get(1),
        n1->get(2) - p->point.get(2),
        1
      );

      Matrix m2(
        n2->get(0) - p->point.get(0),
        n2->get(1) - p->point.get(1),
        n2->get(2) - p->point.get(2),
        1
      );

      p->normal = new Matrix(m1.crossProduct(m2));

    }
  }
  */
}


void Mesh::printMesh() {

  for (int i=0; i<_m*_n; i++) {
    getPoint(i).printPoint();
  }
  
}
