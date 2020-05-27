//example 4 setup: parameters, source, boundary and solution
#include <cmath>

#define _USE_MATH_DEFINES

//system constants: linear densities
/* R [=] ohm/meter, L [=] henry/meter,
   C [=] farad/meter, G [=] siemens/meter */
const double R = 2.0 * M_PI, L = M_PI, C = M_PI, G = 2.0 * M_PI;

//characteristic time for the system
const double charTime = sqrt((L * C) / (G * R));

//characteristic length for the system
const double charLength = 1.0 / sqrt(G * R);

//computation parameters
const double t0 = 0.0, tf = 8.0 * charTime; //time bounds, in seconds
const double z0 = 0.0, zf = 8.0 * charLength; //space bounds, in meters

//quantity of points along t an z axes
const unsigned int NT = 64, NZ = 64;

/* INITIAL AND BOUNDARY CONDITIONS FOR VOLTAGE */
double v_t0(double z) //voltage at t0
{
  return cosh(M_PI * z);
}

double ddt_v_t0(double z) //time derivative of voltage at t0
{
  return -cosh(M_PI * z);
}

double v_z0(double t) //voltage at z0
{
  return exp(-t);
}

double v_zf(double t) //voltage at zf
{
  return exp(-t) * cosh(M_PI);
}

//analytic solution for voltage
double vSln(double t, double z)
{
  return 0.0;
}

/* INITIAL AND BOUNDARY CONDITIONS FOR CURRENT */
double i_t0(double z) //current at t0
{
  return 0.0;
}

double ddt_i_t0(double z) //time derivative of current at t0
{
  return 0.0;
}

double i_z0(double t) //current at z0
{
  return 0.0;
}

double i_zf(double t) //current at zf
{
  return 0.0;
}

//analytic solution for current
double iSln(double t, double z)
{
  return 0.0;
}
