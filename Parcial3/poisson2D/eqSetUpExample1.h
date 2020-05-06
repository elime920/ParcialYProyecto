#include <cmath>

#define _USE_MATH_DEFINES

//equation parameters
double xInit = 0.0, xFin = 0.5, yInit = 0.0, yFin = 0.5;
unsigned int xPoints = 4, yPoints = 4;

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
  return 0.0;
}

//boundary conditions evaluated at xi, yj
double boundBVP(unsigned int i, unsigned int j)
{
  double value = 0.0;
  if (i == 0) value = 0.0;
  else if (j == 0) value = 0.0;
  else if (i == xPoints) value = 200.0 * y(j);
  else if (j == yPoints) value = 200.0 * x(i);
  
  return value;
}
