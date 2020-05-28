//poisson2D class member-function definitions
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include "poisson2D.h"

#define _USE_MATH_DEFINES

//constructor
poisson2D::poisson2D(double xInit, double xFin, double yInit, double yFin, 
                     unsigned int xPoints, unsigned int yPoints, 
                     std::function<double(unsigned int, unsigned int)> sf,
                     std::function<double(unsigned int, unsigned int)> bf)
                     
  : x0(xInit), xF(xFin), y0(yInit), yF(yFin), //extremal points
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
  lambda = pow( ( (Ny * (xF - x0) ) / ( Nx * (yF - y0) ) ), 2 );
  mu = 2.0 * (1.0 + lambda);
}

//source function evaluation
double poisson2D::source(unsigned int i, unsigned int j)
{
  return sFunc(i, j);
}

//boundary function evaluation
double poisson2D::boundary(unsigned int i, unsigned int j)
{
  return bFunc(i, j);
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
      l = i - 1 + (Nx - 1) * (j - 1); //unified index
      
      //source term
      b[l] = pow( (xF - x0) / Nx , 2) * source(i, j);
      
      //boundary terms
      if (i == 1) b[l] -= boundary(0, j);
      if (j == 1) b[l] -= lambda * boundary(i, 0);
      if (i == nx) b[l] -= boundary(Nx, j);
      if (j == ny) b[l] -= lambda * boundary(i, Ny);
    }
  }
}

//solve the system Mw = b for w, using Gauss-Jordan elimination
void poisson2D::solveGaussJordan()
{
  //Row-reduced echelon form of [M | b]
  double value = 0.0, factor = 0.0;
  for (unsigned int i = 0; i < M.size(); i++)
  {
    for (unsigned int j = 0; j < M[0].size(); j++)
    {
      if (fabs(M[i][j]) > std::numeric_limits<double>::epsilon() ) 
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

//solve the system Mw = b for w, using Jacobi iterative method
void poisson2D::solveJacobi(unsigned int N)
{
  unsigned int k = 0;
  double partSum;
  std::vector<double> sln(b.size(), 0.0); //initialize to a null vect.
  
  while ( k < N )
  {
    for (unsigned int i = 0; i < b.size(); i++)
    {
      partSum = 0.0;
      
      for (unsigned int j = 0; j < b.size(); j++)
        {if (j != i) partSum += M[i][j] * sln[j];}
      
      sln[i] = (b[i] - partSum) / M[i][i];
    }
    k += 1;
  }
  b = sln;
}

//solve the system Mw = b for w, using Gauss-Seidel iterative method
void poisson2D::solveGaussSeidel(unsigned int N)
{
  unsigned int k = 0;
  double partSum1, partSum2;
  std::vector<double> sln(b.size(), 0.0); //initialize to a null vect.
  
  while ( k < N )
  {
    for (unsigned int i = 0; i < b.size(); i++)
    {
      partSum1 = 0.0, partSum2 = 0.0;
      
      for (unsigned int j = 0; j < i; j++)
        {partSum1 += M[i][j] * sln[j];}
      
      for (unsigned int j = i + 1; j < b.size(); j++)
        {partSum2 += M[i][j] * sln[j];}
      
      sln[i] = (b[i] - partSum1 - partSum2) / M[i][i];
    }
    k += 1;
  }
  b = sln;
}

//solve the system Mw = b for w, using SOR iterative method
void poisson2D::solveSOR(unsigned int N)
{
  unsigned int k = 0;
  double omega, partSum1, partSum2;
  std::vector<double> sln(b.size(), 0.0); //initialize to a null vect.
  
  omega = 4.0 / ( 2.0 + sqrt( 4.0 - pow( (cos(M_PI / Nx) + cos(M_PI / Ny) ) , 2) ) );
  
  while ( k < N )
  {
    for (unsigned int i = 0; i < b.size(); i++)
    {
      partSum1 = 0.0, partSum2 = 0.0;
      
      for (unsigned int j = 0; j < i; j++)
        {partSum1 += M[i][j] * sln[j];}
      
      for (unsigned int j = i + 1; j < b.size(); j++)
        {partSum2 += M[i][j] * sln[j];}
      
      sln[i] = (1.0 - omega) * sln[i] + 
               omega * (b[i] - partSum1 - partSum2) / M[i][i];
    }
    k += 1;
  }
  b = sln;
}

//execute functions involved to solve the equation
void poisson2D::doSolve(std::string choice, unsigned int N)
{
  setb(); //configure b
  setM(); //configure M

  //solve System
  if (choice == "Gauss-Jordan") solveGaussJordan();
  else if (choice == "Jacobi") solveJacobi(N);
  else if (choice == "Gauss-Seidel") solveGaussSeidel(N);
  else if (choice == "SOR") solveSOR(N);
}

//return the solution: lth component of the solution vector b
double poisson2D::getSln(unsigned int l)
{
  return b[l];
}

//save results to a file as a matrix
void poisson2D::saveAsMatrix(std::string fileName)
{
  std::ifstream readFile; //in case file already exists
  
  readFile.open( fileName.c_str() ); //trying to open the file for input
  
  char userAns;
  if ( !readFile.fail() ) //don't fail: data file exists
  {
    std::cout << "\nA file named '"<< fileName 
              << "' already exists.\n" 
              << "Continue and overwrite? [y/n]: ";
    std::cin >> userAns;
    std::cin.ignore(); //empties buffer
    
    //if user chooses not to overwrite
    if (std::tolower(userAns) == 'n')
    {
      std::cout << "\nFile '" << fileName << "' won't be overwritten,"
                   " process finished." << std::endl;
      exit(1); //finish program execution
    }
  }
  
  readFile.close(); //finish reading process
  
  std::ofstream writeSolution;
  writeSolution.open( fileName.c_str() ); //open the file for input
  
  if ( writeSolution.fail() ) //check successfull opening
  {
    std::cout << "\nFile '" << fileName 
              << "' could not be opened." << std::endl;
    exit(1);
  }
  
  //output file stream format
  writeSolution << std::setiosflags(std::ios::fixed)
                << std::setiosflags(std::ios::showpoint)
                << std::setprecision(4)
                << std::scientific;
                
  //write data to file
  unsigned int l; //unified index
  for (unsigned int j = 0; j <= Ny; j++)
  {
    for (unsigned int i = 0; i <= Nx; i++)
    {
      if ( i == 0 || j == 0 || i == Nx || j == Ny)
        {writeSolution << boundary(i, j) << " ";}
      else
      {
        l = i - 1 + (Nx - 1) * (j - 1);
        writeSolution << b[l] << " ";
      }
    }
    writeSolution << std::endl;
  }
  
  writeSolution.close();
  std::cout << "\nFile " << fileName << " successfully written." << std::endl;
}

//save results to a file as three columns: x, y, w
void poisson2D::saveAsColumns(std::string fileName)
{
  std::ifstream readFile; //in case file already exists
  
  readFile.open( fileName.c_str() ); //trying to open the file for input
  
  char userAns;
  if ( !readFile.fail() ) //don't fail: data file exists
  {
    std::cout << "\nA file named '"<< fileName 
              << "' already exists.\n" 
              << "Continue and overwrite? [y/n]: ";
    std::cin >> userAns;
    std::cin.ignore(); //empties buffer
    
    //if user chooses not to overwrite
    if (std::tolower(userAns) == 'n')
    {
      std::cout << "\nFile '" << fileName << "' won't be overwritten,"
                   " process finished." << std::endl;
      exit(1); //finish program execution
    }
  }
  
  readFile.close(); //finish reading process
  
  std::ofstream writeSolution;
  writeSolution.open( fileName.c_str() ); //open the file for input
  
  if ( writeSolution.fail() ) //check successfull opening
  {
    std::cout << "\nFile '" << fileName 
              << "' could not be opened." << std::endl;
    exit(1);
  }
  
  //output file stream format
  writeSolution << std::setiosflags(std::ios::fixed)
                << std::setiosflags(std::ios::showpoint)
                << std::setprecision(4)
                << std::scientific;
                
  //write data to file
  unsigned int l; //unified index
  for (unsigned int i = 0; i <= Nx; i++)
  {
    for (unsigned int j = 0; j <= Ny; j++)
    {
      if ( i == 0 || j == 0 || i == Nx || j == Ny)
        {writeSolution << x0 + i * (xF - x0) / Nx << " " 
                       << y0 + j * (yF - y0) / Ny << " " 
                       << boundary(i, j) << std::endl;}
      else
      {
        l = i - 1 + (Nx - 1) * (j - 1);
        writeSolution << x0 + i * (xF - x0) / Nx << " " 
                      << y0 + j * (yF - y0) / Ny << " " 
                      << b[l] << std::endl;
      }
    }
  }
  
  writeSolution.close();
  std::cout << "\nFile " << fileName << " successfully written." << std::endl;
}
