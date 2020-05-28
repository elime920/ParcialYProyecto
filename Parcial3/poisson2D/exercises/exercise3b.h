//exercise 3b setup: parameters, source, boundary and solution
#include <cmath>

#define _USE_MATH_DEFINES

//equation parameters
double xInit = 0.0, xFin = M_PI, yInit = 0.0, yFin = 0.5 * M_PI;
double stepX = M_PI / 5.0, stepY = M_PI / 10.0;

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
  return -cos(x(i) + y(j)) - cos(x(i) - y(j));
}

//boundary conditions evaluated at xi, yj
double boundBVP(unsigned int i, unsigned int j)
{
  double value = 0.0;
  if (i == 0) value = cos(y(j));
  else if (j == 0) value = cos(x(i));
  else if (i == xPoints) value = -cos(y(j));
  else if (j == yPoints) value = 0.0;
  
  return value;
}

//analytic solution
double analyticBVP(unsigned int i, unsigned int j)
{
  return cos(x(i)) * cos(y(j));
}
