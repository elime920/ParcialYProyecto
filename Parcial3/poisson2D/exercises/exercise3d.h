//exercise 3d setup: parameters, source, boundary and solution
#include <cmath>

#define _USE_MATH_DEFINES

//equation parameters
double xInit = 1.0, xFin = 2.0, yInit = 1.0, yFin = 2.0;
double stepX = 0.1, stepY = 0.1;

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
  return x(i) / y(j) + y(j) / x(i);
}

//boundary conditions evaluated at xi, yj
double boundBVP(unsigned int i, unsigned int j)
{
  double value = 0.0;
  if (i == 0) value = y(j) * log(y(j));
  else if (j == 0) value = x(i) * log(x(i));
  else if (i == xPoints) value = 2.0 * y(j) * log(2.0 * y(j));
  else if (j == yPoints) value = 2.0 * x(i) * log(2.0 * x(i));
  
  return value;
}

//analytic solution
double analyticBVP(unsigned int i, unsigned int j)
{
  return x(i) * y(j) * log(x(i) * y(j));
}
