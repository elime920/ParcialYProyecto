//problem 1 setup: parameters, source, boundary and solution
#include <cmath>

#define _USE_MATH_DEFINES

//equation parameters
const double T0 = 0.0, TF = 1.0, Z0 = 0.0, ZF = 1.0;
const unsigned int NT = 16, NZ = 16;

const double hT = static_cast<double>((TF - T0) / NT);
const double hZ = static_cast<double>((ZF - Z0) / NZ);

const double k = 1.0;

const double alpha = (0.5 * k * hT - 1.0) / (0.5 * k * hT + 1.0);
const double beta = (2.0 - 2.0 * pow((hT/hZ), 2) - pow(hT, 2))/(0.5 * k * hT + 1.0);
const double lambda = pow((hT/hZ), 2) / (0.5 * k * hT + 1.0);
const double mu = 1.0 - pow((hT/hZ), 2) - 0.5 * pow(hT, 2);
const double nu = hT - 0.5 * k * pow(hT, 2);
const double sigma = 0.5 * pow((hT/hZ), 2);

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

//analytic solution
double exSln(unsigned int i, unsigned int j)
{
  return exp(Z(j) - T(i));
}
