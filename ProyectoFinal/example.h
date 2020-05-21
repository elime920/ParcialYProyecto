//exercise 8 setup: parameters, source, boundary and solution
#include <cmath>

#define _USE_MATH_DEFINES

//equation parameters
double R = 1, C= 1, L=1, G= 1;
double tinit = 0.0, Tmax = 5.0, zinit = 0.0, zfin = 4.0; 
double TInit = pow((G*R)/(L*C),0.5)*tinit;
double TFin = pow((G*R)/(L*C),0.5)*Tmax;
double ZInit = pow(G*R, 0.5)*zinit;
double ZFin = pow(R*R, 0.5)*zfin;
double kcons = pow((G*C)/(G*L), 0.5) + pow((G*L)/(R*C), 0.5);
unsigned int ZPoints = 15, TPoints = 15;

double stepZ = (ZFin - ZInit) / ZPoints;
double stepT = (TFin - TInit) / TPoints;

//outputs x value of index i given
double Z(unsigned int i)
{
  return ZInit + i * stepZ;
}

//outputs y value of index j given
double T(unsigned int j)
{
  return TInit + j * stepT;
}

//condicion inicial en la derivada
double sourceBVP(unsigned int i, unsigned int j)
{
  double value = 0.0;
  if(i == 0) value = -exp(Z(j));
  return value;
}

//boundary conditions evaluated at xi, yj
double boundBVP(unsigned int i, unsigned int j)
{
  double value = 0.0;
  if (i == 0) value = exp(Z(j));
  else if (j == 0) value = exp(-T(i));
  else if (j == ZPoints) value = exp(4-T(i));
  
  return value;
}

//analytic solution
double analyticBVP(unsigned int i, unsigned int j)
{
  return (exp(Z(j) - T(j)));
}
