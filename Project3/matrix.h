#ifndef MATRIX_H
#define MATRIX_H

class Matrix{
private:
  int **m;
  int rows;
  int cols;
public:
  Matrix();
  Matrix(int n_rows, int n_cols);
  //copy constructor
  Matrix(const Matrix &);

  ~Matrix();

  int getRows();
  int getCols();
  int** useMatrix();

  int** addMatrix(int** b);
  int** subMatrix(int** b);
  int** mulMatrix(int** b, int r, int c);

  void printMatrix();
};

#endif
