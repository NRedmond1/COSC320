#include <cstdlib>
#include <iomanip>
#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace std;
#include "matrix.h"

Matrix::Matrix(int r, int c)
{
  rows = r;
  cols = c;
  m = new int*[rows];
  for( int i = 0; i<rows; i++)
    m[i] = new int[cols];

  for(int x=0; x<rows; x++)
    for(int y=0; y<cols; y++)
    {
      m[x][y] = rand()%10;
    }
}

Matrix::Matrix()
{
  rows = 10;
  cols = 10;
  m = new int*[rows];
  for( int i = 0; i<rows; i++)
    m[i] = new int[cols];

  for(int x=0; x<rows; x++)
    for(int y=0; y<cols; y++)
    {
      m[x][y] = rand()%10;
    }
}

Matrix::Matrix(const Matrix &OldMatrix)
{
  rows = OldMatrix.rows;
  cols = OldMatrix.cols;
}

Matrix::~Matrix()
{
  for(int i = 0; i<rows; i++)
    delete [] m[i];
  delete [] m;
}

int Matrix::getRows()
{
  return rows;
}

int Matrix::getCols()
{
  return cols;
}

int** Matrix::useMatrix()
{
  return m;
}

int** Matrix::addMatrix(int** b)
{
  int **c = new int*[rows];
  for( int i = 0; i<rows; i++)
    c[i] = new int[cols];

  for(int i=0; i<rows; i++)
    for(int x=0; x<cols; x++)
    {
      c[i][x] = m[i][x] + b[i][x];
    }
  return c;
}
int** Matrix::subMatrix(int** b)
{
  int **z = new int*[rows];
  for( int i = 0; i<rows; i++)
    z[i] = new int[cols];

  for(int i=0; i<rows; i++)
    for(int x=0; x<cols; x++)
    {
      z[i][x] = m[i][x] - b[i][x];
    }
  return z;
}
int** Matrix::mulMatrix(int** b, int r, int c)
{
  int **t = new int*[rows];
  for( int i = 0; i<rows; i++)
    t[i] = new int[c];

  for( int x=0; x < rows; x++)
    for( int y=0; y < c; y++)
    {
      t[x][y] = 0;
      for( int z=0; z < cols; z++)
        t[x][y] = t[x][y]+(m[x][z]*b[z][y]);
    }

  return t;
}

void Matrix::printMatrix()
{
  for(int i=0; i<rows; i++)
  {
    for(int x=0; x<cols; x++)
    {
      cout << m[i][x] << " ";
    }
    cout << endl;
  }
}
