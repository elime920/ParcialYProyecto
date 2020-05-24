//exercise 8 setup: parameters, source, boundary and solution
#include <cmath>

#define _USE_MATH_DEFINES

//equation parameters
double xInit = 0.0, xFin = 6.0, yInit = 0.0, yFin = 5.0;
unsigned int xPoints = 15, yPoints = 15;

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
  return - (1.5) / (1.04); //- q / K
}

//boundary conditions evaluated at xi, yj
double boundBVP(unsigned int i, unsigned int j)
{
  double value = 0.0;
  if (i == 0) value = y(j) * (5.0 - y(j));
  else if (j == 0) value = x(i) * (6.0 - x(i));
  else if (i == xPoints) value = 0.0;
  else if (j == yPoints) value = 0.0;
  
  return value;
}

//analytic solution: not found for this case
double analyticBVP(unsigned int i, unsigned int j)
{
  return 0.0;
}
