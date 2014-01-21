#include "Mesh.h"

#define IX(row, col) ((row) * _m + (col))

Mesh::Mesh(int m, int n) : _m(m), _n(n) {

  for (int i=0; i<_m *_n; i++) {
    this->mesh.push_back(Matrix(4,1));
  }

}

Matrix Mesh::getPoint(int i) {
  return this->mesh[(size_t)i];
}

Mesh & Mesh::projectOnto(Matrix &projectionMatrix) {

  for (int i=0; i<_m*_n; i++) {
    this->mesh[(size_t)i] = projectionMatrix * this->mesh[(size_t)i];
  }

  return *this;
  
}

Mesh & Mesh::transform(Matrix &transformMatrix) {

  for (int i=0; i<_m*_n; i++) {
    this->mesh[(size_t)i] = transformMatrix * this->mesh[(size_t)i];
  }

  return * this;
}


Mesh & Mesh::homogenize() {
  
  for (int i=0; i<_m*_n; i++) {
    this->mesh[(size_t)i].homogenize();
  }

  return *this;

}

BoundingBox Mesh::getBoundingBox() {

  float minx = this->mesh[0].get(0,0);
  float miny = this->mesh[0].get(1,0);
  float maxx = this->mesh[0].get(0,0);
  float maxy = this->mesh[0].get(1,0);
  
  for (int i=1; i<_m*_n; i++) {
    float x = this->mesh[(size_t)i].get(0,0);
    float y = this->mesh[(size_t)i].get(1,0);

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

std::vector<Micropolygon> Mesh::getMicropolygons() {
  
  std::vector<Micropolygon> polygons;

  for (int i=0; i<_m-1; i++) {
    for (int j=0; j<_n-1; j++) {
     
      Matrix points[4];
      points[0] = this->mesh[ (size_t)IX(i  ,j  ) ];
      points[1] = this->mesh[ (size_t)IX(i  ,j+1) ];
      points[2] = this->mesh[ (size_t)IX(i+1,j  ) ];
      points[3] = this->mesh[ (size_t)IX(i+1,j+1) ];

      
      Micropolygon p(points);
      
      polygons.push_back(p);
    }
  }
  
  return polygons;
}

void Mesh::printMesh() {

  for (int i=0; i<_m*_n; i++) {
    this->mesh[(size_t)i].printPoint();
  }
  
}
