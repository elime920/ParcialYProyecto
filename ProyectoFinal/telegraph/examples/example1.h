//example 1 setup: parameters, source, boundary and solution
#include <cmath>
#include <vector>
#include <functional>

#define _USE_MATH_DEFINES

//computation parameters
const double t0 = 0.0, tf = 1.0; //time bounds, in seconds
const double z0 = 0.0, zf = 1.0; //space bounds, in meters

//system constants: linear densities
/* R [=] ohm/meter, L [=] henry/meter,
   C [=] farad/meter, G [=] siemens/meter */
const double R = 0.1, L = 0.3, C = 2.0 / L, G = 0.2;

//quantity of points along t an z axes
const unsigned int NT = 3, NZ = 3;

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

/*PACKAGE USER INPUT AS VECTORS*/

//vector containing endpoints defined above
std::vector<double> endpoints{t0, tf, z0, zf};

//vector containing system parameters defined above
std::vector<double> params{R, L, C, G};

//vector of functions, containing all boundary conditions for voltage
std::vector<std::function<double(double)>> bcV{v_t0, ddt_v_t0, 
                                               v_z0, v_zf};

//vector of functions, containing all boundary conditions for current
std::vector<std::function<double(double)>> bcI{i_t0, ddt_i_t0, 
                                               i_z0, i_zf};
