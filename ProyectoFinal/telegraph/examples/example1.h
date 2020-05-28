//example 1 setup: parameters, source, boundary and solution
#include <cmath>
#include <vector>
#include <functional>

#define _USE_MATH_DEFINES

//system constants: linear densities
/* R [=] ohm/meter, L [=] henry/meter,
   C [=] farad/meter, G [=] siemens/meter */
const double R = 0.1, L = 0.1, C = 2.0 / L, G = 1.0;

//characteristic time for the system
const double charTime = sqrt((L * C) / (G * R));

//characteristic length for the system
const double charLength = 1.0 / sqrt(G * R);

//computation parameters
const double t0 = 0.0, tf = charTime; //time bounds, in seconds
const double z0 = 0.0, zf = charLength; //space bounds, in meters

//quantity of points along t an z axes
const unsigned int NT = 64, NZ = 64;

/* INITIAL AND BOUNDARY CONDITIONS FOR VOLTAGE */
double v_t0(double z) //voltage at t0
{
  return exp(sqrt(G * R) * z);
}

double ddt_v_t0(double z) //time derivative of voltage at t0
{
  return -0.5 * (R*C + G*L) * exp(sqrt(G * R) * z);
}

double v_z0(double t) //voltage at z0
{
  return exp(-0.5 * (R*C + G*L) * t);
}

double v_zf(double t) //voltage at zf
{
  return exp(sqrt(G * R) * zf - 0.5 * (R*C + G*L) * t);
}

//analytic solution for voltage
double vSln(double t, double z)
{
  return exp(sqrt(R * G) * z - 0.5 * (R*C + G*L) * t);
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
