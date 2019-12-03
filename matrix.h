#ifndef MATRIX_H
#define MATRIX_H

class Matrix{
private:
  double **m;
  int rows;
  int cols;
public:
  Matrix();
  Matrix(int n_rows, int n_cols);
  Matrix(const Matrix &temp);  //copy constructor
  ~Matrix();

  double getRows();
  double getCols();
  double getEntry(int i, int j);
  void setEntry(int i, int j, double val);

  void printMatrix();
  void resize(int newRow, int newCol);
  void randomizeMatrix();

  Matrix Transpose() const;
  double* & operator[](const int &index) const;
  Matrix& operator =(const Matrix &b);
  Matrix operator +(Matrix& b);
  Matrix operator -(Matrix& b);
  Matrix operator *(Matrix& b);

  Matrix Split(int TLRow, int TLCol, int BRRow, int BRCol);
  Matrix OLS(Matrix& B);
  Matrix Inverse();
  Matrix PadMatrix(int power);
  Matrix scaleMatrix(double num);

  Matrix GetBetta();

};

#endif
