#ifndef _MATRIX_H_
#define _MATRIX_H_

class Matrix {

 private:
  int _m, _n;
  float *matrix;

  void allocate(void);

 public:
  
  Matrix();
  Matrix(int);
  Matrix(int, int);
  ~Matrix(void);

  Matrix & operator=(const Matrix &);
  const Matrix operator*(const Matrix &) const;

  void set(int,int,float);
  void setAll(const float[]);
  float get(int,int) const;

  int getM() const { return _m; }
  int getN() const { return _n; }

  static Matrix identity(void);
  void rotate(const Matrix &);
  void scale(const Matrix &);
  void translate(const Matrix &);

};

#endif /* _MATRIX_H_ */
