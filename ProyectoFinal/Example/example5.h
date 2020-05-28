#include <cmath>


#define _USE_MATH_DEFINES

const double t0 = 0.0, tf = 5.0;  //time bounds, in seconds                     
const double z0 = 0.0, zf = 1.0;  //space bounds, in meters                     

// system constants: linear densities                                           
/* R [=] ohm/meter, L[=] henry/meter                                            
   C [=] farad/meter,  G [=] siemens/meter */

/*                                                                              
ALPHA = G/C, BETA = R/L, C2 = 1/L*C, SIGMA = R*G                                
                                                                                
*/

const double ALPHA = 2.0, BETA = 2.0, C2 = 1/pow(M_PI,2), SIGMA = (ALPHA*BETA)/\
C2;

//quantity of points along t and z axes                                         
const unsigned int NT = 100, NZ = 100;

/* INITIAL AND BOUNDARY CONDITIONS FOR VOLTAGE */

double v_t0(double z)  //voltage at t0                                          
{
  return cosh(M_PI*z);
}

double ddt_v_t0(double z)  //time derivative of voltage at t0                   
{
  return -cosh(M_PI*z);
}

double v_z0(double t) //voltage at z0                                           
{
  return exp(-t);
}

double v_zf(double t) //voltage at zf                                           
{
  return exp(-t)*cosh(M_PI);
}

//analytic solution for voltage                                                 

double vSln(double t, double z)
{
  return exp(-t)*cosh(M_PI*z);
}

/* INITIAL AND BOUNDARY CONDITIONS FOR CURRENT */
double i_t0(double z)  //current at t0                                          
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

//analytical solution for current                                               
double iSln(double t, double z)
{
  return 0.0;
}
