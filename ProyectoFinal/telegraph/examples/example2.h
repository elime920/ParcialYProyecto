//example 2 setup: parameters, source, boundary and solution
#include <cmath>
#include <vector>
#include <functional>

#define _USE_MATH_DEFINES

//computation parameters
const double t0 = 0.0, tf = 4.0; //time bounds, in seconds
const double z0 = 0.0, zf = 4.0; //space bounds, in meters

//system constants: linear densities
/* R [=] ohm/meter, L [=] henry/meter,
   C [=] farad/meter, G [=] siemens/meter */
const double R = 0.1, L = 1.0, C = 0.1, G = 1.0;

//quantity of points along t an z axes
const unsigned int NT = 10, NZ = 10;

/* INITIAL AND BOUNDARY CONDITIONS FOR VOLTAGE */
double v_t0(double z) //voltage at t0
{
  return 0.0;
}

double ddt_v_t0(double z) //time derivative of voltage at t0
{
  return 0.0;
}

double v_z0(double t) //voltage at z0
{
  return sin(8.0 * t);
}

double v_zf(double t) //voltage at zf
{
  return 0.0;
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
