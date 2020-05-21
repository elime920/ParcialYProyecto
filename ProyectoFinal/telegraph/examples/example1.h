//problem 1 setup: parameters, source, boundary and solution
#include <cmath>

#define _USE_MATH_DEFINES

//equation parameters
const double T0 = 0.0, TF = 1.0, Z0 = 0.0, ZF = 1.0;
const unsigned int NT = 4, NZ = 4;

const double hT = static_cast<double>((TF - T0) / NT);
const double hZ = static_cast<double>((ZF - Z0) / NZ);

const double k = 1.0;

//outputs T value of index i given
double T(unsigned int i)
{
  return T0 + i * hT;
}

//outputs Z value of index j given
double Z(unsigned int j)
{
  return Z0 + j * hZ;
}

//boundary condition: function at T0
double atilde(unsigned int j)
{
  return exp(Z(j));
}

//boundary condition: time derivative of function at T0
double btilde(unsigned int j)
{
  return -exp(Z(j));
}

//boundary condition: function at Z0
double ctilde(unsigned int i)
{
  return exp(-T(i));
}

//boundary condition: function at ZF
double dtilde(unsigned int i)
{
  return exp(1.0 - T(i));
}

//boundary function compilation
double boundFunc(unsigned int i, unsigned int j)
{
  double outVal = 0.0;
  
  if (i == 0) outVal = atilde(j);
  if (j == 0) outVal = ctilde(i);
  if (j == NZ) outVal = dtilde(i);
  
  return outVal;
}

//time derivative at T0 function
double initDerFunc(unsigned int j)
{
  return btilde(j);
}

//analytic solution
double exSln(unsigned int i, unsigned int j)
{
  return exp(Z(j) - T(i));
}
