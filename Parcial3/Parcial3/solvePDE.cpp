//solvePDE class member-functions definitions
#include <iostream>
#include <cmath>
#include <vector>
#include "solvePDE.h"

#define _USE_MATH_DEFINES

/*
function definitions
*/

//constructor
solvePDE::solvePDE()
  : Nx(6), Ny(5), dim((Nx - 1) * (Ny - 1)),
  boundAndSource(dim, 0), M(Ny - 1, std::vector<double>(Nx - 1, 0))
{
  //variables initialization
  x0 = 0.0, xN = 2.0;
  y0 = 0.0, yN = 1.0;
  hx = static_cast<double>( (xN - x0) / Nx );
  hy = static_cast<double>( (yN - y0) / Ny );
  lambda = pow((hx / hy), 2);
  mu = 2.0 * (1.0 + lambda);
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

//create the matrix associated to the BVP
void solvePDE::setSysM()
{
  unsigned int nrows = M.size(), ncols = M[0].size();
  for (unsigned int i = 0; i < nrows; i++)
  {
    for (unsigned int j = 0; j < ncols; j++)
    {
      //unified index
      unsigned int l = (i + 1) + (Nx - 1) * (j);
      
      //filling inhomogeneous part
      boundAndSource[l] += source(i, j);

      //bottom border of the region
      if (i == 0) M[i][j] += 1;
      
      //left border of the region
      if (j == 0) M[i][j] += 2;

      //right border of the region
      if (j == ncols-1) M[i][j] += 3;
      
      //top border of the region
      if (i == nrows-1) M[i][j] += 4;
      
      //not on the borders of the matrix
      if (i > 0 && i < nrows-1 && j > 0 && j < ncols-1) M[i][j] += 5;
    }
  }
}

//print system matrix
void solvePDE::printSysM()
{
  for (unsigned int i = 0; i < M.size(); i++)
  {
    for (unsigned int j = 0; j < M[0].size(); j++)
    {
      std::cout << M[i][j] << " ";
    }
  std::cout << std::endl;
  }
}
