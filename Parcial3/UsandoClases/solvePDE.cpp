//solvePDE class member-functions definitions
#include <iostream>
#include <cmath>
#include <vector>
#include "solvePDE.h"

#define _USE_MATH_DEFINES

//constructor
solvePDE::solvePDE()
  : Nx(6), Ny(5), dim((Nx - 1) * (Ny - 1)),
    b(dim, 0), M(dim, std::vector<double>(dim, 0))
{
  //variables initialization
  x0 = 0.0, xN = 2.0;
  y0 = 0.0, yN = 1.0;
  hx = static_cast<double>( (xN - x0) / Nx );
  hy = static_cast<double>( (yN - y0) / Ny );
  lambda = pow((hx / hy), 2);
  mu = 2.0 * (1.0 + lambda);
}

//destructor
solvePDE::~solvePDE()
{
  std::cout << "Finish PDE solver." << std::endl;
}

//outputs x value of index i given
double solvePDE::getX(unsigned int i)
{
  return x0 + i * hx;
}

//outputs y value of index j given
double solvePDE::getY(unsigned int j)
{
  return y0 + j * hy;
}

//outputs the value of Nx
unsigned short int solvePDE::getNx()
{
  return Nx;
}

//outputs the value of Ny
unsigned short int solvePDE::getNy()
{
  return Ny;
}

//source function f(x, y) evaluated at xi, yj
double solvePDE::source(unsigned int i, unsigned int j)
{
  return getX(i) * exp(getY(j));
}

//boundary conditions
double solvePDE::boundary(unsigned int i, unsigned int j)
{
  double value = 0.0;
  if (i == 0) value = 0.0;
  else if (j == 0) value = getX(i);
  else if (i == Nx) value = 2.0 * exp(getY(j));
  else if (j == Ny) value = M_E * getX(i);
  
  return value;
}

//set the matrix associated to the BVP
void solvePDE::setSysM()
{
  unsigned int nx = Nx - 1, ny = Ny - 1;
  for (unsigned int row = 0; row < M.size(); row++)
  {
    for (unsigned int col = 0; col < M[0].size(); col++)
    {
      if (row == col) M[row][col] = -mu;
      if (col >= nx) M[col - nx][col] = lambda;
      if (row >= nx) M[row][row - nx] = lambda;
      if (((col + 1) % nx) > 0) M[col+1][col] = 1;
      if (((row + 1) % nx) > 0) M[row][row+1] = 1;
    }
  }
}

//set the inhomogeneous part of the system, consisting of
//boundary terms and the source function f(x, y)
void solvePDE::setSysb()
{
  unsigned int i, j, l;
  for (j = 1; j < Ny; j++)
  {
    for (i = 1; i < Nx; i++)
    {
      l = i - 1 + (Nx - 1) * (j - 1);
      b[l] = hx * hx * source(i, j);

      if (i == 1) b[l] -= boundary(0, j);
      if (j == 1) b[l] -= lambda * boundary(i, 0);
      if (i == Nx - 1) b[l] -= boundary(Nx, j);
      if (j == Ny - 1) b[l] -= lambda * boundary(i, Ny);
    }
  }
}

//print b
double solvePDE::getSysb(unsigned int l)
{
  return b[l];
}

//solve the system Mw = b
void solvePDE::GaussLinearSolve()
{
  //Row-reduced echelon form of [M | w]
  double value = 0.0, factor = 0.0;
  for (unsigned int i = 0; i < M.size(); i++)
  {
    for (unsigned int j = 0; j < M[0].size(); j++)
    {
      if (fabs(M[i][j]) > 1.0e-15) 
      {
        value = M[i][j];
        
        //divide all the row i by its first non-zero element
        for (unsigned int k = 0; k < M[0].size(); k++)
        {
          M[i][k] /= value;
        }
        b[i] /= value;
        
        //place ones on all values behind the pivot
        for (unsigned int l = 0; l < M.size(); l++)
        {
          if (l != i) 
          {
            factor = M[l][j];
            for (unsigned int m = 0; m < M[0].size(); m++)
            {
              M[l][m] -= factor * M[i][m];
            }
              b[l] -= factor * b[i];
          }
        }
        break;
      }
    }
  }
}
