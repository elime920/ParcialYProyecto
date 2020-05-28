//example 3 setup: parameters, source, boundary and solution
//pseudo standing wave
#include <cmath>

#define _USE_MATH_DEFINES

//system constants: linear densities
/* R [=] ohm/meter, L [=] henry/meter,
   C [=] farad/meter, G [=] siemens/meter */
//const double R = 2.0e-1, L = 6.1e-7, C = 5.157e-11, G = 7.2e-11;
const double R = 1.0, L = 1.0, C = 1.0, G = 1.0;

//characteristic time for the system
const double charTime = sqrt((L * C) / (G * R));

//characteristic length for the system
const double charLength = 1.0 / sqrt(G * R);

//computation parameters
const double t0 = 0.0, tf = 8*charTime; //time bounds, in seconds
const double z0 = 0.0, zf = 8*charLength; //space bounds, in meters

//quantity of points along t an z axes
const unsigned int NT = 128, NZ = 128;

/* INITIAL AND BOUNDARY CONDITIONS FOR VOLTAGE */
double v_t0(double z) //voltage at t0
{
  return sin(M_PI * z / charLength);
}

double ddt_v_t0(double z) //time derivative of voltage at t0
{
  return 0.0;
}

double v_z0(double t) //voltage at z0
{
  return 0.0;
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
