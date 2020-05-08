//example 2 setup: parameters, source, boundary and solution
#include <cmath>

#define _USE_MATH_DEFINES

//equation parameters
double xInit = 0.0, xFin = 2.0, yInit = 0.0, yFin = 1.0;
unsigned int xPoints = 6, yPoints = 5;

double stepX = (xFin - xInit) / xPoints;
double stepY = (yFin - yInit) / yPoints;

//outputs x value of index i given
double x(unsigned int i)
{
  return xInit + i * stepX;
}

//outputs y value of index j given
double y(unsigned int j)
{
  return yInit + j * stepY;
}

//source function f(x, y) evaluated at xi, yj
double sourceBVP(unsigned int i, unsigned int j)
{
  return x(i) * exp(y(j));
}

//boundary conditions evaluated at xi, yj
double boundBVP(unsigned int i, unsigned int j)
{
  double value = 0.0;
  if (i == 0) value = 0.0;
  else if (j == 0) value = x(i);
  else if (i == xPoints) value = 2.0 * exp(y(j));
  else if (j == yPoints) value = M_E * x(i);
  
  return value;
}

//analytic solution
double analyticBVP(unsigned int i, unsigned int j)
{
  return x(i) * exp(y(j));
}
