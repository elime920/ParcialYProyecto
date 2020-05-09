//exercise 2 setup: parameters, source, boundary and solution
#include <cmath>

#define _USE_MATH_DEFINES

//equation parameters
double xInit = 1.0, xFin = 2.0, yInit = 0.0, yFin = 1.0;
double stepX = 1.0 / 3.0, stepY = 1.0 / 3.0;

unsigned int xPoints = static_cast<unsigned int>((xFin-xInit)/stepX);
unsigned int yPoints = static_cast<unsigned int>((yFin-yInit)/stepY);

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
  return 0.0;
}

//boundary conditions evaluated at xi, yj
double boundBVP(unsigned int i, unsigned int j)
{
  double value = 0.0;
  if (i == 0) value = log(1.0 + pow(y(j), 2));
  else if (j == 0) value = 2.0 * log(x(i));
  else if (i == xPoints) value = log(4.0 + pow(y(j), 2));
  else if (j == yPoints) value = log(pow(x(i), 2) + 1.0);
  
  return value;
}

//analytic solution
double analyticBVP(unsigned int i, unsigned int j)
{
  return log( pow(x(i), 2) + pow(y(j), 2) );
}
