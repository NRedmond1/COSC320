#include <iostream>
using namespace std;
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include "matrix.h"

Matrix::Matrix(int r, int c)
{
  rows = r;
  cols = c;
  m = new double*[rows];
  for( int i = 0; i<rows; i++)
    m[i] = new double[cols];

  for(int x=0; x<rows; x++)
    for(int y=0; y<cols; y++)
    {
      m[x][y] = 0;
    }
}

Matrix::Matrix()
{
  rows = 10;
  cols = 10;
  m = new double*[rows];
  for( int i = 0; i<rows; i++)
    m[i] = new double[cols];

  for(int x=0; x<rows; x++)
    for(int y=0; y<cols; y++)
    {
      m[x][y] = 0;
    }
}

Matrix::Matrix(const Matrix &temp)
{
  rows = temp.rows;
  cols = temp.cols;

  m = new double*[rows];
  for(int i = 0; i<rows; i++)
  {
    m[i] = new double[cols];
  }

  for(int i=0; i<rows; i++)
  {
    for(int j=0; j<cols; j++)
    {
      m[i][j] = temp.m[i][j];
    }
  }
}

Matrix::~Matrix()
{
  for(int i = 0; i<rows; i++)
    delete [] m[i];
  delete [] m;
}

double Matrix::getRows()
{
  return rows;
}

double Matrix::getCols()
{
  return cols;
}

Matrix& Matrix::operator =(const Matrix &b)
{
    if (this != &b)
    {
      for(int i = 0; i<rows; i++)
        delete [] m[i];
      delete [] m;

      rows = b.rows;
      cols = b.cols;

      m = new double*[rows];
      for(int i = 0; i<rows; i++)
      {
        m[i] = new double[cols];
      }

      for(int i=0; i<rows; i++)
      {
        for(int j=0; j<cols; j++)
        {
          m[i][j] = b.m[i][j];
        }
      }

    }
    return (*this);
}

Matrix Matrix::operator +( Matrix & a )
{
    if (a.getRows()!= this->getRows()|| a.getCols() != this->getCols() )
    {
        std:: cout << "error: Sizes are different" << std:: endl;
        return *this;
    }

    Matrix b(rows, cols);
    for ( int i = 0 ; i < a.getRows(); i++ )
    {
        for (int j = 0; j < a.getCols(); j++ )
        {
            b.m[i][j] = double(this->m[i][j]+a.m[i][j]);
        }
    }

    return b;
}

Matrix Matrix::operator -( Matrix& a )
{
  if (a.getRows()!= this->getRows()|| a.getRows() != this->getCols() )
  {
      std:: cout << "error: Sizes are different" << std:: endl;
      return *this;
  }

  Matrix b(this->getRows(), this->getCols());
  for ( int i = 0 ; i < a.getRows(); ++i )
  {
      for (int j = 0; j < a.getCols(); ++j )
      {
          b.m[i][j] = double(this->m[i][j] - a.m[i][j]);
      }
  }

  return b;
}

//template <typename T>
Matrix Matrix::operator *(Matrix& a)
{
  if( this->getCols() == a.getRows() )
  {
    Matrix c(this->getRows(), a.getCols());
    for( int i = 0; i < this->rows; ++i)
        for(int j = 0; j < a.cols; ++j)
            for( int k = 0; k < a.rows; ++k)
                c.m[i][j] += double(this->m[i][k] * a.m[k][j]);

    return c;
  }
  else
  {
    cout << "error: Unmatching matrix sizes." << endl;
    return *this;
  }
}

double* & Matrix::operator [](const int &index) const  // overloading operator []
{
  return  m[index];
}

Matrix Matrix::Transpose() const
{
	//int Size=Columns*Rows;
	Matrix Temp(cols, rows);
	for (int i=0; i < rows; i++)
		for(int j=0; j < cols; j++)
		    Temp[j][i] = m[i][j];

	return Temp;
}

void Matrix::resize(int newRow, int newCol)
{
  rows = newRow;
  cols = newCol;
}

double Matrix::getEntry( int i,  int j) {
    if (i >= getRows() || j >= getCols() || i < 0 || j < 0)
    {
        std::cout << "error: Wrong index, matrix size is not matching" << std::endl;
        return 00;
    }
    else
        return m[i][j];
 }

 void Matrix::setEntry( int i, int j, double val)
 {
     if (i >= getRows() || j >= getCols() || i < 0 || j < 0)
     {
         std::cout << "error: Wrong index, matrix size is not matching" << std::endl;
         return;
     }
     else
        m[i][j] = val;
 }

 void Matrix::randomizeMatrix()
 {
   for(int i = 0; i < this->rows; i++)
     for(int j = 0; j < this->cols; j++)
     {
       this->m[i][j] = rand()%10;
     }

 }

 Matrix Matrix::scaleMatrix(double num)
 {
   Matrix temp(rows, cols);
   for(int i = 0; i < rows; i++)
   {
     for(int j = 0; j < cols; j++)
     {
         temp[i][j] = double(num * m[i][j]);
     }
   }
   return temp;
 }

Matrix Matrix::Split( int TLRow, int TLCol, int BRRow, int BRCol )
{
  int size_rows = BRRow - TLRow;
  int size_cols = BRCol - TLCol;

  Matrix temp(this->rows/2, this->cols/2);

  for(int x = TLRow; x <= BRRow; x++)
    for(int y = TLCol; y <= BRCol; y++)
    {
        temp.m[x - TLRow][y - TLCol] = m[x][y];
    }

  return temp;
}

Matrix Matrix::PadMatrix(int power)
{
  if(ceil(log2(rows)) == floor(log2(rows)))
    if ( ceil(log2(cols)) == floor(log2(cols)) )
      return (*this);

  Matrix temp(pow(2, power), pow(2, power));
  for(int x = 0; x < temp.getRows(); x++)
    for(int y = 0; y < temp.getCols(); y++)
    {
      if(x == y)
        temp.m[x][y] = 1;
      else
        temp.m[x][y] = 0;
    }

  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++)
    {
      temp.m[i][j] = m[i][j];
    }

  return temp;
}

Matrix Matrix::Inverse()
{
  if( this->getRows() == 1 )
  {
    Matrix inv(this->getRows(), this->getCols());
    inv[0][0] = 1 / this->m[0][0];
    return inv;
  }

  int power = 0;
  while(this->getRows() > pow(2, power))
  {
      power++;
  }

  Matrix TEMP = this->PadMatrix(power);
  Matrix B = TEMP.Split(0, 0, (TEMP.rows/2)-1, (TEMP.cols/2)-1);
  Matrix C = TEMP.Split(TEMP.rows/2, 0, TEMP.rows-1, (TEMP.cols/2)-1);
  Matrix CT = TEMP.Split(0, TEMP.cols/2, (TEMP.rows/2)-1, TEMP.cols-1);
  //Matrix CT = C.Transpose();
  Matrix D = TEMP.Split(TEMP.rows/2, TEMP.cols/2, TEMP.rows-1, TEMP.cols-1);

  Matrix BInv = B.Inverse();
  Matrix W = C*BInv;
  Matrix WT = BInv*CT;
  Matrix X = W*CT;
  Matrix S = D-X;
  Matrix V = S.Inverse();
  Matrix Y = V*W;
  Matrix YT = Y.Transpose();
  Matrix T = YT.scaleMatrix(-1);
  Matrix U = Y.scaleMatrix(-1);
  Matrix Z = WT*Y;
  Matrix R = BInv + Z;

  Matrix Temp_Inv(TEMP.rows, TEMP.cols);

  for(int a = 0; a < TEMP.rows/2; a++)
    for(int b = 0; b < TEMP.cols/2; b++)
    {
      Temp_Inv[a][b] = R[a][b];
    }

  for(int c = TEMP.rows/2; c < TEMP.rows; c++)
    for(int d = 0; d < TEMP.cols/2; d++)
    {
      Temp_Inv[c][d] = U[c-TEMP.cols/2][d];
    }

  for(int e = 0; e < TEMP.rows/2; e++)
    for(int f = TEMP.cols/2; f < TEMP.cols; f++)
    {
      Temp_Inv[e][f] = T[e][f-TEMP.cols/2];
    }

  for(int g = TEMP.rows/2; g < TEMP.rows; g++)
    for(int h = TEMP.cols/2; h < TEMP.cols; h++)
    {
      Temp_Inv[g][h] = V[g-TEMP.rows/2][h-TEMP.cols/2];
    }

  Matrix resized(this->getRows(), this->getCols());
  for(int i = 0; i < this->getRows(); i++)
      for(int j = 0; j < this->getCols(); j++)
      {
        resized[i][j] = Temp_Inv[i][j];
      }

  return resized;
}

Matrix Matrix::GetBetta()
{
  int colNumb = this->cols - 1;
  Matrix B(this->rows, 1);
  for( int i = 0; i < this->rows; i++ )
  {
    B.m[i][0] = this->m[i][colNumb];
  }
  return B;

}

Matrix Matrix::OLS( Matrix& B )
{
  Matrix A(this->rows, this->cols);
  for( int i = 0; i < this->rows; i++ )
    for( int j = 0; j < this->cols; j++ )
    {
      if( j == this->cols - 1 )
        A.m[i][j] = 1;
      else
        A.m[i][j] = this->m[i][j];
    }

  Matrix I = (A.Transpose() * A);
  Matrix IIN = I.Inverse();
  Matrix AT = A.Transpose();
  Matrix T = IIN*AT;
  Matrix TB = T * B;

  return TB;
}

void Matrix::printMatrix()
{
  for(int i=0; i<getRows(); i++)
  {
    for(int x=0; x<getCols(); x++)
    {
      cout << m[i][x] << " ";
    }
    cout << endl;
  }
}
