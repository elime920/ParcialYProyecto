//header, definition of class solvePDE
#include <iostream>
#include <cmath>
#include <vector>

//class solvePDE definition
class solvePDE
{
  public:
  solvePDE(); //constructor
  ~solvePDE(); //destructor
  
  double getX(unsigned int); //outputs x value of index given
  double getY(unsigned int); //outputs y value of index given
  
  //get parameters
  unsigned short int getNx();
  unsigned short int getNy();
  
  double source(unsigned int, unsigned int); //source function f(x, y)
  double boundary(unsigned int, unsigned int); //boundary conditions
  
  void setSysM(); //create the matrix associated to the BVP
  
  void setSysb(); //set inhomogeneity vector b
  double getSysb(unsigned int);
  
  void GaussLinearSolve(); //solve linear system

  private:
  //problem parameters and constants
  unsigned short int Nx, Ny, dim;
  double x0, xN;
  double y0, yN;
  double hx, hy;
  double lambda, mu;
  std::vector<double> b; //bound and source terms
  std::vector<std::vector<double>> M;

}; //end class solvePDE
