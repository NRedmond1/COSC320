#include "matrix.h"
#include <cstdlib>
#include <iomanip>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
 *******************************************
 *
 *  Nathan Redmond
 *  COSC 320 Project 1
 *  Created: 10 March 2019
 *  Modified: 24 March 2019
 *
 ********************************************
 */
int main(int argc, char** argv)
{
  int num_rows = 0;
  int num_cols = 1;
  if( argc < 2 )
    cout << "No file as argument available" << endl;
  else
  {
    std::string fname = std::string(argv[1]);
    ifstream inFile;
    inFile.open(fname);
    if (!inFile)
    {
      cout << "Can't open input file " << fname << endl;
      return 1;
    }

    char temp[100];
    while(!inFile.eof())
    {
      inFile.getline(temp, 100, '\n');
      num_rows++;
    }
    num_rows = num_rows - 1;

    for(int i = 0; i < 100; i++)
    {
      if(temp[i] == ' ')
        num_cols++;
    }

    if( num_cols < 2 )
    {
      cout << "One dimention input. Can not calculate OLS." << endl;
      return 1;
    }
    inFile.close();
    inFile.open(fname);

    Matrix POINTS(num_rows, num_cols);
    double point;
    for(int x = 0; x < num_rows; x++)
      for(int y = 0; y < num_cols; y++)
      {
        inFile >> point;
        POINTS[x][y] = point;
      }

    Matrix t = POINTS.GetBetta();
    Matrix OLS = POINTS.OLS(t);

    cout << "LEAST SQUARES LINEAR REGRESSION: " << endl;
    for(int t = OLS.getRows()-1; t >= 0; t--)
    {
      if( t == 0 )
        cout << OLS[OLS.getRows()-1][0] << endl;
      else if( t == 1 )
        cout << OLS[OLS.getRows()-2][0] << "x + ";
      else
        cout << OLS[OLS.getRows()-1-t][0] << "x^" << t << " + ";
    }
    inFile.close();

  }

  srand (time(NULL));
  int oper, rows, cols, rows2, cols2;
  bool operation = true;
  cout << "CREATE TWO MATRICIES FOR TESTING." << endl;
  cout << "First Matrix number of rows: ";
  cin >> rows;
  cout << "First Matrix number of columns: ";
  cin >> cols;
  cout << "Second Matrix number of rows: ";
  cin >> rows2;
  cout << "Second Matrix number of columns: ";
  cin >> cols2;
  cout << endl;

  Matrix a(rows, cols);
  Matrix b(rows2, cols2);
  a.randomizeMatrix();
  b.randomizeMatrix();

  Matrix c(a.getRows(), b.getCols());

  cout << "Matrix a" << endl;
  a.printMatrix();
  cout << endl;

  cout << "Matrix b" << endl;
  b.printMatrix();
  cout << endl;

  cout << "ADD a+b" << endl;
  c = a+b;
  c.printMatrix();
  cout << endl;

  cout << "SUBTRACT a-b" << endl;
  c = a-b;
  c.printMatrix();
  cout << endl;

  cout << "MULTIPLY a*b" << endl;
  Matrix Mul(a.getRows(), b.getCols());
  Mul = a*b;
  Mul.printMatrix();
  cout << endl;

  cout << "SCALAR of a" << endl;
  Matrix Scal(a.getRows(), a.getCols());
  Scal = a.scaleMatrix(3);
  Scal.printMatrix();
  cout << endl;

  cout << "TRANSPOSE of a" << endl;
  Matrix t(a.getCols(), a.getRows());
  t = a.Transpose();
  t.printMatrix();
  cout << endl;

//----------------------------------------------------

  cout << "BETTA of a" << endl;
  Matrix temp = a.GetBetta();
  temp.printMatrix();
  cout << endl;

  cout << "OLS of the Matrix of Points: " << endl;
  Matrix lls = a.OLS(temp);
  lls.printMatrix();
  cout << endl;


}
