//poisson2D class member-function definitions
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "Telegrapher.h"

#define _USE_MATH_DEFINES

//constructor
Telegrapher::Telegrapher(double TInit, double TFin, double ZInit,
			 double Zfin, double ZFin,double kcons,
			 double stepZ, double stepT,
		         unsigned int TPoints, unsigned int ZPoints, 
                         std::function<double(unsigned int, unsigned int)> sf,
                         std::function<double(unsigned int, unsigned int)> bf)
                     
  : T0(TInit), T(TFin), Z0(ZInit), ZF(ZFin), //extremal points
    NT(TPoints), NZ(ZPoints), //quantity of points on t and z axes
    k(kcons), hZ(stepZ), hT(stepT),  
    sFunc(sf), bFunc(bf), //source and boundary functions
    dim((NT+1)*(NZ+1)), //size of matrix approximations.
    W(dim, std::vector<double>(dim, 0)) // matrix W.
{
  std::cout << "Soluciones para la línea de transmisión.\n" << std::endl;
  std::cout << "-------Ecuaciones del telégrafo--------\n" << std::endl;
  //Use the initialized parameters to set the secondary ones
  setComputationParams();
}

//destructor
Telegrapher::~Telegrapher()
{
  std::cout << "\nEl programa llegó a su final." << std::endl;
}

//set the computation parameters lambda and mu
void Telegrapher::setComputationParams()
{

  lambda = pow( hT/hZ , 2 ) * pow(((k*hT)/2)+1,-1);
  beta = (2.0 - 2.0*pow(hT/hZ,2)-pow(hT,2))/(k*hT/2.0 + 1.0);
  alpha = (k*hT/2.0 - 1)/(k*hT/2.0 + 1);
  mu = 1.0 - pow(hT/hZ,2) - pow(hT,2)/2;
  sigma = pow(hT/hZ,2)/2;
  nu = hT - k*pow(hT,2)/2;
}

//auxiliary function to connect indices to argument function
double Telegrapher::evalOnIndices(unsigned int i, unsigned int j, 
                  std::function<double(unsigned int, unsigned int)> func)
{
  return func(i, j);
}

//source function evaluation
double Telegrapher::source(unsigned int i, unsigned int j)
{
  return evalOnIndices(i, j, sFunc);
}

//boundary function evaluation
double Telegrapher::boundary(unsigned int i, unsigned int j)
{
  return evalOnIndices(i, j, bFunc);
}

//set the matrix associated to the BVP
void Telegrapher::setW()
{
 
  for (unsigned int row = 0; row < W.size(); row++)
  {
    for (unsigned int col = 0; col < W[0].size(); col++)
    {
      if (row == 0) W[row][col] = boundary(0,col);
      if (col == 0) W[row][col] = boundary(row,0);
      if (col == Nz-1) W[row][col] = boundary(row,Nz);

      if (row == 1) W[row][col] = mu * boundary(0,col) + nu * source(0,col) + sigma* (boundary(0,col-1) +boundary(0,col+1));

      if (row > 1 && row <= NT-1 && col > 0) W[row+1][col] = alpha*W[row-1][col] + beta* W[row][col] + lambda* (W[row][col-1]+ W[row][col+1]);
    }
  }
}

//set the vector of boundary and source functions


double Telegrapher::getSln(unsigned int i, unsigned int j)
{
  return W[i][j];
}
