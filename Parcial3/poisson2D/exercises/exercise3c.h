//exercise 3c setup: parameters, source, boundary and solution
#include <cmath>

#define _USE_MATH_DEFINES

//equation parameters
double xInit = 0.0, xFin = 2.0, yInit = 0.0, yFin = 1.0;
double stepX = 0.2, stepY = 0.1;

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
  if (i == 0) value = 1.0;
  else if (j == 0) value = 1.0;
  else if (i == xPoints) value = exp(2.0 * y(j));
  else if (j == yPoints) value = exp(x(i));
  
  return value;
}

//analytic solution
double analyticBVP(unsigned int i, unsigned int j)
{
  return exp(x(i) * y(j));
}
