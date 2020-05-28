//Program to test class "telegraph"
#include <iostream>
#include <iomanip>
#include "telegraph.h"
#include "examples/exampleEXPCOSH.h"

#define printIndex std::left << std::setw(2)
#define printReal std::right << std::setw(7) << std::fixed << std::setprecision(4)
#define printScN std::setw(7) << std::scientific << std::setprecision(1)

int main()
{
  /*PACKAGE USER INPUT AS VECTORS*/

  //vector containing endpoints
  std::vector<double> endpoints{t0, tf, z0, zf};

  //vector containing system parameters
  std::vector<double> params{R, L, C, G};

  //vector of functions, containing all boundary conditions for voltage
  std::vector<std::function<double(double)>> bcV{v_t0, ddt_v_t0, 
                                                 v_z0, v_zf};

  //vector of functions, containing all boundary conditions for current
  std::vector<std::function<double(double)>> bcI{i_t0, ddt_i_t0, 
                                                 i_z0, i_zf};

  //object creation: bvp stands for Boundary Value Problem
  telegraph bvp(endpoints, params, bcV, bcI, NT, NZ);
  
  //show characteristic time and length of the system
  std::cout << "Characteristic time for the system: " 
            << printScN << charTime << " seconds. \n"
            << "Characteristic length for the system: " 
            << printScN << charLength << " meters." << std::endl;

  bvp.setwV(); //solve for voltage
  bvp.setwI(); //solve for current
  
  //print solution
  double vSol = 0.0, iSol = 0.0;
  std::cout << "Solution printing:" << std::endl;
  std::cout << "i  j | ti      zj     | wV(i,j) V(i,j) | |V-wV| |"
               " wI(i,j) I(i,j) | |I-wI| " << std::endl;
  
  for (unsigned int l = 0; l < 74; l++) std::cout << "-"; 
  std::cout << std::endl;
  
  for (unsigned int i = 0; i <= NT; i++)
  {
    for (unsigned int j = 0; j <= NZ; j++)
    {
      vSol = vSln(charTime * bvp.getT(i), charLength * bvp.getZ(j));
      iSol = iSln(charTime * bvp.getT(i), charLength * bvp.getZ(j));
      
      std::cout << printIndex << i << " " 
                << printIndex << j << "|"
                << printReal << charTime * bvp.getT(i) << " " 
                << printReal << charLength * bvp.getZ(j) << " |"
                << printReal << bvp.getwV(i, j) << " "
                << printReal << vSol << " |" 
                << printScN << fabs(vSol - bvp.getwV(i, j)) << "||"
                << printReal << bvp.getwI(i, j) << " "
                << printReal << iSol << " |" 
                << printScN << fabs(iSol - bvp.getwI(i, j)) << "|"
                << std::endl;
    }
  } //end printing
  
  //write to files
  bvp.saveToFile("V", "Columns", "outputCols.dat");
  bvp.saveToFile("V", "Matrix", "outputMatrix.dat");

  return(0);
} //end main
