//poisson2D class member-function definitions
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include "poisson2D.h"

#define _USE_MATH_DEFINES

//constructor
poisson2D::poisson2D(double xInit, double xFin, double yInit, double yFin, 
                     unsigned int xPoints, unsigned int yPoints, 
                     std::function<double(unsigned int, unsigned int)> sf,
                     std::function<double(unsigned int, unsigned int)> bf)
                     
  : x0(xInit), xN(xFin), y0(yInit), yN(yFin), //extremal points
    Nx(xPoints), Ny(yPoints), //quantity of points on x and y axes
    sFunc(sf), bFunc(bf), //source and boundary functions
    dim((Nx - 1) * (Ny - 1)), //size of vector and matrix implementations
    b(dim, 0), M(dim, std::vector<double>(dim, 0)) //vector b, matrix M
{
  std::cout << "Poisson two dimensional PDE solver started.\n" << std::endl;
  //Use the initialized parameters to set the secondary ones
  setComputationParams();
}

//destructor
poisson2D::~poisson2D()
{
  std::cout << "\nPoisson two dimensional PDE solver finished." << std::endl;
}

//set the computation parameters lambda and mu
void poisson2D::setComputationParams()
{
  lambda = pow( ( (Ny * (xN - x0) ) / ( Nx * (yN - y0) ) ), 2 );
  mu = 2.0 * (1.0 + lambda);
}

//auxiliary function to connect indices to argument function
double poisson2D::evalOnIndices(unsigned int i, unsigned int j, 
                  std::function<double(unsigned int, unsigned int)> func)
{
  return func(i, j);
}

//source function evaluation
double poisson2D::source(unsigned int i, unsigned int j)
{
  return evalOnIndices(i, j, sFunc);
}

//boundary function evaluation
double poisson2D::boundary(unsigned int i, unsigned int j)
{
  return evalOnIndices(i, j, bFunc);
}

//set the matrix associated to the BVP
void poisson2D::setM()
{
  unsigned int nx = Nx - 1, ny = Ny - 1; //reduced indices
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

//set the vector of boundary and source functions
void poisson2D::setb()
{
  unsigned int nx = Nx - 1, ny = Ny - 1; //reduced indices
  unsigned int i, j, l;
  for (j = 1; j < Ny; j++)
  {
    for (i = 1; i < Nx; i++)
    {
      l = i - 1 + (Nx - 1) * (j - 1); //unified indices
      
      //source term
      b[l] = pow( (xN - x0) / Nx , 2) * source(i, j);
      
      //boundary terms
      if (i == 1) b[l] -= boundary(0, j);
      if (j == 1) b[l] -= lambda * boundary(i, 0);
      if (i == nx) b[l] -= boundary(Nx, j);
      if (j == ny) b[l] -= lambda * boundary(i, Ny);
    }
  }
}

//solve the system Mw = b for w, using Gauss-Jordan elimination
void poisson2D::GaussLinearSolve()
{
  //Row-reduced echelon form of [M | w]
  double value = 0.0, factor = 0.0;
  for (unsigned int i = 0; i < M.size(); i++)
  {
    for (unsigned int j = 0; j < M[0].size(); j++)
    {
      if (fabs(M[i][j]) > 1.0e-15) 
      {
        value = M[i][j]; //first non-zero element
        
        //divide all the ith row by its first non-zero element
        for (unsigned int k = 0; k < M[0].size(); k++)
        {
          M[i][k] /= value;
        }
        b[i] /= value; //do the same for vector b
        
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
              b[l] -= factor * b[i]; //same for vector b
          }
        }
        break; //go to the next row (out of j - for loop)
      }
    }
  }
}

//execute functions involved to solve the equation
void poisson2D::doSolve()
{
  setb(); //configure b
  setM(); //configure M
  GaussLinearSolve(); //solve System
}

//return the lth component of the solution vector b
double poisson2D::getb(unsigned int l)
{
  return b[l];
}