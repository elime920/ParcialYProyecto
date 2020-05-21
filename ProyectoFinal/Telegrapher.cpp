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
			 double ZFin, double kcons,
			 double stepZ, double stepT,
		         unsigned int TPoints, unsigned int ZPoints, 
                         std::function<double(unsigned int, unsigned int)> sf,
                         std::function<double(unsigned int, unsigned int)> bf)
                     
  : T0(TInit), T(TFin), Z0(ZInit), ZF(ZFin), //extremal points
    NT(TPoints), NZ(ZPoints), //quantity of points on t and z axes
    k(kcons), hZ(stepZ), hT(stepT),  
    sFunc(sf), bFunc(bf), //source and boundary functions
    W(NT+1, std::vector<double>(NT +1, 0)) // matrix W.
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
void Telegrapher::setfirstline(unsigned int j)
{
  for(j = 1; j < NZ; j++)
    {
      W[1][j] = mu*boundary(0,j) + nu*source(0,j) +
	        sigma*(boundary(0,j-1) + boundary(0,j+1));
    }
}

void Telegrapher::Bounds(unsigned int i, unsigned int j)
{
  for(i = 0; i <= NT; i++)
    {
      for(j = 0; j <= NZ; j++)
	{
	  if(i == 0) W[i][j] = boundary(0,j);
	  if(j == 0) W[i][j] = boundary(i,0);
	  if(j == NZ) W[i][j] = boundary(i,NZ);
	}
    }
}

void Telegrapher::Inner(unsigned int i, unsigned int j)
{
  for(i = 0; i <= NT; i++)
    {
      for(j = 0; j <= NZ; j++)
	{
	  if(i > 0 && i < NT && j > 0 && j < NZ)
	    {
	      W[i+1][j] = alpha*W[i-1][j] + beta * W[i][j] +
		          lambda * (W[i][j-1] + W[i][j+1]);
	    }
	}
    }
}

//set the vector of boundary and source functions


double Telegrapher::getSln(unsigned int i, unsigned int j)
{
  return W[i][j];
}
